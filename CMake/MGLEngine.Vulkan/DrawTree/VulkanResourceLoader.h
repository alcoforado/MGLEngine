#pragma once
#include<vector>
#include <MGLEngine.Shared\Utils\CommitTag.h>
#include <MGLEngine.Vulkan\DrawTree\IVulkanResourceLoader.h>

#include <MGLEngine.Vulkan\RenderResources\VulkanDescriptorSet.h>


template<class T>
class ResourceLoaderAccessor
{

private:
	CommitTag* _pTag;
	std::vector<T>* _pValue;

public:
	ResourceLoaderAccessor(CommitTag* pTag, std::vector<T>* pValue)
	{
		assert(pTag);
		assert(pValue);
		_pValue = pValue;
		_pTag = pTag;
	}

	void set(const T& value)
	{
		(*_pValue)[0] = value;
		_pTag->Next();
	}

};



template<class SlotType>
class ResourceLoaderPerFrame : public IVulkanResourceLoader
{
public:
	using DataType = typename SlotType::ElemData;
private:
	SlotType* _pSlot;
	CommitTag _cTag;
	std::vector<DataType> _values;
	std::vector<VulkanDescriptorSet*> _vDS; //descritpor sets, one for each frame
public:
	
	ResourceLoaderPerFrame(SlotType* pSlot, std::vector<VulkanDescriptorSet*>& v) {
		_cTag = CommitTag::NewTagChain();
		_pSlot = pSlot;
		_vDS = v;
		_values.resize(pSlot->size());
	}
	
	ResourceLoaderAccessor<DataType> GetAccessor() {
		return ResourceLoaderAccessor<DataType>(&_cTag, &_values);
	}

	void virtual OnFrameInit(TreeExecutionContext* pContext) override {
		eassert(pContext->GetDrawContext().GetFrameSize() == _vDS.size(),"The number of datasets doesn't match the number of frames");
		auto currentFrameIndex = pContext->GetDrawContext().GetFrameIndex();
		
		auto pBinding = _vDS[currentFrameIndex]->GetBinding(_pSlot);
		if (pBinding->Tag != _cTag)
		{
			_vDS[currentFrameIndex]->setValue(_pSlot, IArray<DataType>(_values));
			
		}
	}
	void virtual OnExecution(TreeExecutionContext* pContext) override {
		int currentFrameIndex = pContext->GetDrawContext().GetFrameIndex();
		VulkanCommandBuffer* pComm = pContext->GetCommandBuffer();
		pComm->BindDescriptorSet(pContext->GetPipeline(), _vDS[currentFrameIndex]);

	}


};


