#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/DrawTree.h>
#include "../Shaders/IVulkanRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../VulkanContext/IDrawContext.h"
class IVulkanRenderContext;

template<class T>
class VulkanDrawTreeParser
{
	DrawTree<T> &_tree;
	VulkanPipeline& _pipeline;
	VulkanBuffer<T>* _pVerticesBuffer;
	std::vector<VulkanCommandBuffer*> _commands;
	IVulkanRenderContext& _context;
public:
	VulkanDrawTreeParser(IVulkanRenderContext& context, VulkanPipeline& pipeline, DrawTree<T>& tree)
		:_context(context), _pipeline(pipeline), _tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline.IsLoaded());
		_pVerticesBuffer = new VulkanBuffer<T>(context.GetMemoryManager(), 0, 100);

	}

	void clearCommandsBuffers()
	{
		for (auto cmd : _commands)
		{
			delete cmd;
		}
		_commands.clear();
	}


	VulkanSemaphore* ExecuteTree(IDrawContext *drawContext)
	{
		NTreeNode<DrawInfo<T>>* root = _tree.GetRoot();
		_tree.ComputeSizes();
		bool needRedraw = false;
		if (_tree.NeedRedraw())
		{
			needRedraw = true;
			//If draw tree changed, Update Vertice Data 
			std::vector<unsigned> indices1(100);
			Indices is1(indices1.data(), root->GetData().Current.SizeI, 100);
			std::vector<unsigned> indices2(100);
			Indices is2(indices2.data(), root->GetData().Future.SizeI, 100);

			if (root->GetData().Future.SizeV > _pVerticesBuffer->capacity())
			{
				VulkanBuffer<T> *newBuff = new VulkanBuffer<T>(_context.GetMemoryManager(), root->GetData().Future.SizeV, root->GetData().Future.SizeV);
				_tree.UpdateVerticeData(*_pVerticesBuffer, is1, *newBuff, is2);

				delete _pVerticesBuffer;
				_pVerticesBuffer = newBuff;
				is1.swap(is2);
			}
			else
			{

				_tree.UpdateVerticeData(*_pVerticesBuffer, is1);
			}
		}
		if (drawContext->IsWindowResized())
			_pipeline.OnSwapChainReload(&(drawContext->GetRenderContext()->GetSwapChain()));

		if (needRedraw || drawContext->IsWindowResized())
		{
			//Redo the commands
			clearCommandsBuffers();
			auto framebuffers = _pipeline.GetVulkanSwapChainFramebuffers();
			glm::vec4 color(0, 0, 0, 1.0);
			for (int i = 0; i < framebuffers->Size(); i++)
			{
				auto framebuffer = framebuffers->GetFramebuffer(i);
				VulkanCommandBuffer* comm = _context.GetLogicalDevice()->GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().SimultaneousUse());
				comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 0));
				comm->BindPipeline(&_pipeline);
				comm->BindVertexBuffer(_pVerticesBuffer->GetHandle());
				comm->Draw(static_cast<uint32_t>(_pVerticesBuffer->size()), 1, 0, 0);
				comm->EndRenderPass();
				comm->End();
				_commands.push_back(comm);
			}
		}
		uint32_t index = _pipeline.GetSwapChain().GetCurrentImageIndex();
		return GetCommandForFrame(index)->SubmitPipelineAsync(drawContext->GetSemaphore(), VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT);
	}


	~VulkanDrawTreeParser()
	{
		if (_pVerticesBuffer)
		{
			delete _pVerticesBuffer;
		}
		clearCommandsBuffers();
	}

	VulkanCommandBuffer* GetCommandForFrame(uint32_t index)
	{
		assert(index < _commands.size());
		return _commands[index];
	}
};

