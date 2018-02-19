#pragma once
#include <MGLEngine.Shared/Utils/DrawTree/DrawTree.h>
#include "../Shaders/IVulkanRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../VulkanContext/IDrawContext.h"
#include "MGLEngine.Vulkan/MemoryManager/VulkanMappedAutoSyncBuffer.h"
#include "MGLEngine.Vulkan/RenderResources/VulkanRenderResourceLoadContext.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBatchCollection.h>
class IVulkanRenderContext;



template<class T>
class VulkanDrawTreeParser
{

	DrawTree<T> &_tree;
	VulkanPipeline& _pipeline;
	VulkanMappedAutoSyncBuffer<T>* _pVerticesBuffer;

	struct PerFrameData
	{
		OPointer<VulkanCommandBuffer> CB;
		bool IsDirty;
	};
	std::vector<PerFrameData> _perFrameData;
	
	IVulkanRenderContext& _context;
	OPointer<VulkanSemaphore> _sm;
	VulkanRenderResourceLoadContext _renderLoadContext;

private:
	VulkanCommandBuffer* GetRootNodeLoadCommands(DrawInfo<T> *root)
	{
		assert(root->DrawInfoType == DrawInfoType::Root);

		if (root->HasDirtyResources())
		{
			_renderLoadContext._loadCommandBuffer.if_free();

			_renderLoadContext._loadCommandBuffer = _context.GetLogicalDevice()->GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().OneTimeSubmit());

			for (auto r : root->GetResources())
			{
				r->Load(); //Load All resources
			}

			//Add a memory barrier

			//_renderLoadContext._loadCommandBuffer.PipelineBarrier();


		}
		return nullptr;
	}

public:
	VulkanDrawTreeParser(IVulkanRenderContext& context, VulkanPipeline& pipeline, DrawTree<T>& tree)
		:_context(context), _pipeline(pipeline), _tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline.IsLoaded());
		_pVerticesBuffer = new VulkanMappedAutoSyncBuffer<T>(context.GetMemoryManager(), 0, 100,{VK_BUFFER_USAGE_VERTEX_BUFFER_BIT});
		_sm = new VulkanSemaphore(context.GetLogicalDevice());
		_perFrameData = std::vector<PerFrameData>(pipeline.GetVulkanSwapChainFramebuffers()->Size(),PerFrameData());
	}


	IVulkanRenderResourceLoadContext* GetRenderLoadContext() { return &_renderLoadContext; }

	void clearCommandsBuffers()
	{
		for (auto cmd : _perFrameData)
		{
			cmd.IsDirty = true;
		}
	}



	void ExecuteTree(IDrawContext *drawContext)
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
				VulkanMappedAutoSyncBuffer<T> *newBuff = new VulkanMappedAutoSyncBuffer<T>(_context.GetMemoryManager(), root->GetData().Future.SizeV, root->GetData().Future.SizeV, {VK_BUFFER_USAGE_VERTEX_BUFFER_BIT});
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
		}
		
		PerFrameData &frameData = _perFrameData[drawContext->GetFrameIndex()];
		if (frameData.IsDirty)
		{
			auto framebuffer = _pipeline.GetVulkanSwapChainFramebuffers()->GetFramebuffer(drawContext->GetFrameIndex());
			glm::vec4 color(0, 0, 0, 1.0);

			frameData.CB.if_free();

			VulkanCommandBuffer *comm = _context.GetLogicalDevice()->GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().SimultaneousUse());
			comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 0));
			comm->BindPipeline(&_pipeline);
			comm->BindVertexBuffer(_pVerticesBuffer->GetHandle());
			this->ParseTree(comm,&_tree);
			comm->Draw(static_cast<uint32_t>(_pVerticesBuffer->size()), 1, 0, 0);
			comm->EndRenderPass();
			comm->End();
			frameData.CB = comm;
			frameData.IsDirty = false;
			
		}
		
		uint32_t index = _pipeline.GetSwapChain().GetCurrentImageIndex();
		VulkanCommandBuffer* rootCmds = GetRootNodeLoadCommands(&(_tree.GetRoot()->GetData()));
	
		VulkanSemaphore *rootSemaphore = nullptr;
		VulkanSemaphore *endSemaphore = drawContext->GetAvailableSemaphore();
		if (rootCmds != nullptr)
		{
			rootSemaphore = drawContext->GetAvailableSemaphore();
			drawContext->Out.CommandBatch.AddBatch( rootCmds , rootSemaphore, nullptr, { });
		}
		drawContext->Out.CommandBatch.AddBatch(frameData.CB, endSemaphore, rootSemaphore, { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT });
		
		
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


	void ParseTree(VulkanCommandBuffer* comm, DrawTree<T> *tree)
	{
		tree->GetRoot()->ForAllPreOrderControlDescent([&](NTreeNode<DrawInfo<T>>* pNode)->bool {
			DrawInfo<T> &data = pNode->GetData();
				if (data.DrawInfoType==DrawInfoType::Root)
				{
					return true;
				}
				return true;
		});
	}

	




};

