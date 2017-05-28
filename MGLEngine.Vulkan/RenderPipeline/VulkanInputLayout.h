#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include <glm/detail/type_vec2.hpp>

class VulkanInputLayout;

template<class VerticeData>
class InputBinding
{
	VulkanInputLayout *_layout;

	InputBinding(VulkanInputLayout *layout)
	{
		_layout = layout;
	}
	InputBinding& AddField(glm::vec2 VerticeData::*member)
	{
		AddField(member.)
		return *this;
	}
};

class VulkanInputLayout
{
	
	VkPipelineInputAssemblyStateCreateInfo InputAssembly;
	std::vector<VkVertexInputBindingDescription> _vBindings;
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
		return  InputBinding<VerticeData>();
	}

	VkPipelineInputAssemblyStateCreateInfo GetPipelineInputAssmeblyStateCreateInfo();

};

