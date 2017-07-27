#pragma once
#include "Utils/DrawTree/DrawTree.h"
#include "../Shaders/IRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../VulkanContext/IDrawContext.h"
class IRenderContext;
template<class T>
class VulkanDrawTreeParser
{
	DrawTree<T> &_tree;
	VulkanPipeline& _pipeline;
	VulkanStagingBuffer<T>* _pVerticesBuffer;
	std::vector<VulkanCommandBuffer*> _commands;
	IRenderContext& _context;
public:
	VulkanDrawTreeParser(IRenderContext& context,  VulkanPipeline& pipeline,DrawTree<T>& tree)
		:_context(context),_pipeline(pipeline),	_tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline.IsLoaded());
		_pVerticesBuffer = new VulkanStagingBuffer<T>(context.GetMemoryManager(), 0,100);
		
	}
	
	void clearCommandsBuffers()
	{
		for (auto cmd : _commands)
		{
			delete cmd;
		}

	}

	
	void ExecuteTree(IDrawContext *drawContext)
	{
		NTreeNode<DrawInfo<T>>* root = _tree.GetRoot();
		_tree.ComputeSizes();
		if (_tree.NeedRedraw())
		{

			//If draw tree changed, Update Vertice Data 
			std::vector<unsigned> indices1(100);
			Indices is1(indices1.data(), root->GetData().Current.SizeI, 100);
			std::vector<unsigned> indices2(100);
			Indices is2(indices2.data(), root->GetData().Future.SizeI, 100);

			if (root->GetData().Future.SizeV > _pVerticesBuffer->capacity())
			{
				VulkanStagingBuffer<T> *newBuff = new VulkanStagingBuffer<T>(_context.GetMemoryManager(), root->GetData().Future.SizeV, root->GetData().Future.SizeV);
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

		if (_tree.NeedRedraw() || drawContext->IsWindowResized())
		{
		//Redo the commands
		clearCommandsBuffers();
		auto framebuffers = _pipeline.GetVulkanSwapChainFramebuffers();
		glm::vec4 color(0, 0, 0, 1.0);
		for (int i = 0; i<framebuffers->Size(); i++)
		{
			auto framebuffer = framebuffers->GetFramebuffer(i);
			VulkanCommandBuffer* comm = new VulkanCommandBuffer(_context.GetCommandPool());
			comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 0));
			comm->BindPipeline(&_pipeline);
			comm->BindVertexBuffer(_pVerticesBuffer->GetHandle());
			comm->Draw(static_cast<uint32_t>(_pVerticesBuffer->size()), 1, 0, 0);
			comm->EndRenderPass();
			comm->End();
			_commands.push_back(comm);
		}
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

