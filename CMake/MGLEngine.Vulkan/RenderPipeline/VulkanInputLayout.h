#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glm/detail/type_vec2.hpp>
#include <typeinfo>
#include <MGLEngine.Shared/Utils/Exception.h>
class VulkanInputLayout;

template<class VerticeData>
class InputBinding
{
	std::vector<VkVertexInputAttributeDescription> *_attributes;
public:
	InputBinding(std::vector<VkVertexInputAttributeDescription> *v)
	{
		_attributes = v;
	}
	template<class T>
	VkFormat TypeToVulkanFormat()
	{
		if (typeid(T) == typeid(glm::vec2))
		{
			return VK_FORMAT_R32G32_SFLOAT; 
		}
		if (typeid(T) == typeid(glm::vec3))
		{
			return VK_FORMAT_R32G32B32_SFLOAT;
		}
		throw new Exception("Can't get Vulkan Format from type %s", typeid(T).name());
	}
	template<class FieldType>
	InputBinding<VerticeData>& AddField(uint32_t loc,FieldType VerticeData::*member)
	{
		VkVertexInputAttributeDescription attr = {};
		VerticeData v;
		attr.binding = 0;
		attr.location = loc;
		attr.format = TypeToVulkanFormat<FieldType>();
		attr.offset = static_cast<uint32_t>(reinterpret_cast<char*>(&(v.*member)) - reinterpret_cast<char*>(&v));
		_attributes->push_back(attr);
		return *this;
	}
};

class VulkanInputLayout
{
	
	VkPipelineVertexInputStateCreateInfo VertexInputInfo;
	std::vector<VkVertexInputBindingDescription> _vBindings;
	std::vector<VkVertexInputAttributeDescription> _vAttributes;
public:
	            VulkanInputLayout();
	~VulkanInputLayout();
	
	template<class VerticeData>
	InputBinding<VerticeData> CreateBinding()
	{
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(VerticeData);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		_vBindings.push_back(bindingDescription);
		return  InputBinding<VerticeData>(&_vAttributes);
	}

	VkPipelineVertexInputStateCreateInfo* GetPipelineInputAssmeblyStateCreateInfo()
	{
		VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		VertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(_vBindings.size());
		VertexInputInfo.pVertexBindingDescriptions =  _vBindings.data(); // Optional
		VertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(_vAttributes.size());
		VertexInputInfo.pVertexAttributeDescriptions = _vAttributes.data(); // Optional
		return &VertexInputInfo;
	}

};

