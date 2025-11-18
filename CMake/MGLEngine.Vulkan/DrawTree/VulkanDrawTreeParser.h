#pragma once
#include <MGLEngine.Shared/DrawTree/DrawTree.h>
#include "../Shaders/IVulkanRenderContext.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include "../VulkanContext/IDrawContext.h"
#include <MGLEngine.Vulkan/MemoryManager/VulkanMappedAutoSyncBuffer.h>
#include <MGLEngine.Vulkan/DrawTree/TreeExecutionContext.h>
#include <MGLEngine.Vulkan/VulkanContext/VulkanCommandBatchCollection.h>
#include "MGLEngine.Vulkan/RenderResources/IVulkanRenderSlot.h"
#include <MGLEngine.Vulkan/RenderResources/SlotManager.h>
#include <MGLEngine.Vulkan/RenderResources/VulkanDescriptorSet.h>
#include <MGLEngine.Vulkan/DrawTree/VulkanInternalData.h>


class IVulkanRenderContext;

template<class VerticeData>
using VulkanDrawTree = DrawTree<VerticeData, VulkanInternalData>;

template<class T>
class VulkanDrawTreeParser
{

	VulkanDrawTree<T>& _tree;
	VulkanPipeline* _pPipeline;
	VulkanMappedAutoSyncBuffer<T>* _pVerticesBuffer;
	struct PerFrameData
	{
		std::shared_ptr<VulkanCommandBuffer> CB;
		bool IsDirty;
		VulkanDescriptorSet* DescriptorSet;
		PerFrameData() { IsDirty = true; DescriptorSet = nullptr; }
	};
	std::vector<PerFrameData> _perFrameData;


	IVulkanRenderContext* _pContext;
	OPointer<VulkanSemaphore> _sm;

	std::string _oncePerFrameDescriptSetLayout;
private:
	void TriggerFrameInitForResourceLoaders(TreeExecutionContext* pExecContext)
	{

		for (s_ptr<IVulkanResourceLoader> loader : _tree.GetRoot()->GetData().InternalEngineData().resourceLoaders)
		{
			loader->OnFrameInit(pExecContext);
		}

	}

	void DrawShapes(TreeExecutionContext* pExecContext)
	{

		_tree.GetRoot()->ForAllPreOrderControlDescent([&](VulkanDrawTree<T>::Node* pNode)->bool {

			typename VulkanDrawTree<T>::DrawInfoT& info = pNode->GetData();
			if (info.IsBatch() || info.IsRoot())
			{
				for (s_ptr<IVulkanResourceLoader> loader : info.InternalEngineData().resourceLoaders)
				{
					loader->OnExecution(pExecContext);
				}

			}
			if (info.IsBatch())
			{
				VulkanCommandBuffer *pComm=pExecContext->GetCommandBuffer();
				pComm->Draw(info.Future.SizeV, 1, info.Future.OffV, 0);
			}


			return info.IsRoot(); //just go one level down;
		});

	}

public:
	VulkanDrawTreeParser(IVulkanRenderContext* context, VulkanPipeline* pipeline, VulkanDrawTree<T>& tree, std::string  oncePerFrameDescriptSetLayout = "")
		:_pContext(context), _pPipeline(pipeline), _tree(tree)
	{
		_pVerticesBuffer = nullptr;
		assert(pipeline->IsLoaded());
		_pVerticesBuffer = new VulkanMappedAutoSyncBuffer<T>(context->GetMemoryManager(), 0, 100, { VK_BUFFER_USAGE_VERTEX_BUFFER_BIT });
		_sm = new VulkanSemaphore(context->GetLogicalDevice());
		_perFrameData = std::vector<PerFrameData>(pipeline->GetVulkanSwapChainFramebuffers()->Size(), PerFrameData());
		_oncePerFrameDescriptSetLayout = oncePerFrameDescriptSetLayout;

		if (oncePerFrameDescriptSetLayout != "")
		{
			_pPipeline->GetSlotManager()->AllocateDescritorSets(oncePerFrameDescriptSetLayout, (int)_perFrameData.size());
		}
	}



	void setAllFramesToRedraw()
	{
		for (PerFrameData& frameData : _perFrameData)
		{
			frameData.IsDirty = true;
		}
	}





	void ExecuteTree(IDrawContext* drawContext)
	{
		int frameIndex = drawContext->GetFrameIndex();

		TreeExecutionContext execContext(drawContext, _pPipeline);
		TriggerFrameInitForResourceLoaders(&execContext);



		typename VulkanDrawTree<T>::Node* root = _tree.GetRoot();
		_tree.ComputeSizes();
		bool needRedraw = _tree.NeedRedraw();

		const VulkanBuffer<T>* pVerticeBuffer = this->Serialize();




		if (drawContext->IsWindowResized())
			_pPipeline->OnSwapChainReload(drawContext->GetRenderContext()->GetSwapChain());





		if (needRedraw || drawContext->IsWindowResized())
		{
			//set all frames as need to update
			setAllFramesToRedraw();
		}

		PerFrameData& frameData = _perFrameData[frameIndex];
		if (frameData.IsDirty)
		{
			auto framebuffer = _pPipeline->GetVulkanSwapChainFramebuffers()->GetFramebuffer(drawContext->GetFrameIndex());
			glm::vec4 color(0, 0, 0, 1.0);



			VulkanCommandBuffer* comm = _pContext->GetLogicalDevice()->GetGraphicCommandPool()->CreateCommandBuffer(VulkanCommandBufferOptions().SimultaneousUse());
			execContext.SetCommandBuffer(comm);


			comm->BeginRenderPass(framebuffer, glm::vec4(0, 0, 0, 1.0));
			comm->BindPipeline(_pPipeline);
			comm->BindVertexBuffer(pVerticeBuffer->GetHandle());

			DrawShapes(&execContext);

			comm->Draw(static_cast<uint32_t>(_pVerticesBuffer->size()), 1, 0, 0);
			comm->EndRenderPass();
			comm->End();
			frameData.CB = std::shared_ptr<VulkanCommandBuffer>(comm);
			frameData.IsDirty = false;

		}

		uint32_t index = drawContext->GetFrameIndex();
		drawContext->Out.Commands.push_back(frameData.CB.get());



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
		assert(index < this->_perFrameData.size());
		return this->_perFrameData[index].CB;
	}

	const VulkanBuffer<T>* Serialize()
	{
		typename VulkanDrawTree<T>::Node* root = _tree.GetRoot();
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
				VulkanMappedAutoSyncBuffer<T>* newBuff = new VulkanMappedAutoSyncBuffer<T>(_pContext->GetMemoryManager(), root->GetData().Future.SizeV, root->GetData().Future.SizeV, { VK_BUFFER_USAGE_VERTEX_BUFFER_BIT });
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








};

