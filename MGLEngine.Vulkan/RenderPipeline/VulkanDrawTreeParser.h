#pragma once
#include <MGLEngine.Shared/DrawTree/DrawTree.h>
#include "../Shaders/IVulkanRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../VulkanContext/IDrawContext.h"
#include "MGLEngine.Vulkan/MemoryManager/VulkanMappedAutoSyncBuffer.h"
#include "MGLEngine.Vulkan/RenderResources/VulkanResourceLoadContext.h"
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBatchCollection.h>
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <MGLEngine.Vulkan/RenderResources/SlotManager.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>


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
		VulkanDescriptorSet *DescriptorSet;
		PerFrameData() { IsDirty = true; DescriptorSet = nullptr; }
	};
	std::vector<PerFrameData> _perFrameData;
	

	IVulkanRenderContext& _context;
	OPointer<VulkanSemaphore> _sm;

	VulkanRenderResourceLoadContext _renderLoadContext;

private:
	

public:
	VulkanDrawTreeParser(IVulkanRenderContext& context, VulkanPipeline& pipeline, DrawTree<T>& tree,int layoutPerFrame=-1)
		:_context(context), _pipeline(pipeline), _tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline.IsLoaded());
		_pVerticesBuffer = new VulkanMappedAutoSyncBuffer<T>(context.GetMemoryManager(), 0, 100,{VK_BUFFER_USAGE_VERTEX_BUFFER_BIT});
		_sm = new VulkanSemaphore(context.GetLogicalDevice());
		_perFrameData = std::vector<PerFrameData>(pipeline.GetVulkanSwapChainFramebuffers()->Size(),PerFrameData());
		
		if (layoutPerFrame != -1)
		{
			_pipeline.GetSlotManager()->AllocateDescritorSets(layoutPerFrame, (int) _perFrameData.size());
			int i = 0;
			for (auto f : _perFrameData)
			{
				f.DescriptorSet = _pipeline.GetSlotManager()->GetDescriptorSet(layoutPerFrame, i++);
			}
		}
	}


	IVulkanResourceLoadContext* GetRenderLoadContext() { return &_renderLoadContext; }

	void setAllFramesToRedraw()
	{
		for (auto frameData : _perFrameData)
		{
			frameData.IsDirty = true;
		}
	}

	void ExecuteTree(IDrawContext *drawContext)
	{
		NTreeNode<DrawInfo<T>>* root = _tree.GetRoot();
		_tree.ComputeSizes();
		bool needRedraw = _tree.NeedRedraw();
		
		const VulkanBuffer<T>* pVerticeBuffer = this->Serialize(_tree);

		if (drawContext->IsWindowResized())
			_pipeline.OnSwapChainReload(drawContext->GetRenderContext()->GetSwapChain());


		
		if (needRedraw || drawContext->IsWindowResized())
		{
			//set all frames as need to update
		    setAllFramesToRedraw();
		}
		
		PerFrameData &frameData = _perFrameData[drawContext->GetFrameIndex()];
		if (frameData.IsDirty)
		{
			auto framebuffer = _pipeline.GetVulkanSwapChainFramebuffers()->GetFramebuffer(drawContext->GetFrameIndex());
			glm::vec4 color(0, 0, 0, 1.0);

			frameData.CB.if_free();

			VulkanCommandBuffer *comm = _context.GetLogicalDevice()->GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().SimultaneousUse());
			comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 1.0));
			comm->BindPipeline(&_pipeline);
			comm->BindVertexBuffer(pVerticeBuffer->GetHandle());
			comm->Draw(static_cast<uint32_t>(_pVerticesBuffer->size()), 1, 0, 0);
			comm->EndRenderPass();
			comm->End();
			frameData.CB = comm;
			frameData.IsDirty = false;
			
		}
		
		uint32_t index = drawContext->GetFrameIndex();
		drawContext->Out.Commands.push_back(frameData.CB);


		
	}

	~VulkanDrawTreeParser()
	{
		if (_pVerticesBuffer)
		{
			delete _pVerticesBuffer;
		}
		setAllFramesToRedraw();
	}

	VulkanCommandBuffer* GetCommandForFrame(uint32_t index)
	{
		assert(index < _commands.size());
		return _commands[index];
	}

	const VulkanBuffer<T>* Serialize(DrawTree<T>& tree)
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
				VulkanMappedAutoSyncBuffer<T> *newBuff = new VulkanMappedAutoSyncBuffer<T>(_context.GetMemoryManager(), root->GetData().Future.SizeV, root->GetData().Future.SizeV, { VK_BUFFER_USAGE_VERTEX_BUFFER_BIT });
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
		return _pVerticesBuffer->GetVulkanBuffer();
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

