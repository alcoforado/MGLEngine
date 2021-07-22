#pragma once
#include <vulkan/vulkan.h>
#include <MGLEngine.Shared/Utils/Exception.h>
#include "VulkanUtils.h"
#include <map>
#include <fstream>
#include <MGLEngine.Shared/Utils/eassert.h>
std::ofstream vulkanError("vulkan_log.txt", std::ofstream::trunc);



std::vector<std::string> ConvertToVectorString(std::vector<const char*> user)
{
	std::vector<std::string> result;
	for (int i = 0; i < user.size(); i++)
	{
		result.push_back(user[i]);
	}
	return result;
}


std::vector<const char*> ConvertToVectorChar(const std::vector<std::string>& user)
{
	std::vector<const char*> result;
	for (int i = 0; i < user.size(); i++)
	{
		result.push_back(user[i].c_str());
	}
	return result;
}



void AssertVulkanSuccess(VkResult res) 
{
	if (res != VK_SUCCESS)
	{
		throw new Exception("Error Result: %s", MapVkResultToString(res));
	}
}
std::string MapVkResultToString(VkResult result)  
{
	static std::map<int, std::string> map;
	if (map.size() == 0)
	{
		map[VK_SUCCESS] = "VK_SUCCESS";
		map[VK_NOT_READY] = "VK_NOT_READY";
		map[VK_TIMEOUT] = "VK_TIMEOUT";
		map[VK_EVENT_SET] = "VK_EVENT_SET";
		map[VK_EVENT_RESET] = "VK_EVENT_RESET";
		map[VK_INCOMPLETE] = "VK_INCOMPLETE";
		map[VK_ERROR_OUT_OF_HOST_MEMORY] = "VK_ERROR_OUT_OF_HOST_MEMORY";
		map[VK_ERROR_OUT_OF_DEVICE_MEMORY] = "VK_ERROR_OUT_OF_DEVICE_MEMORY";
		map[VK_ERROR_INITIALIZATION_FAILED] = "VK_ERROR_INITIALIZATION_FAILED";
		map[VK_ERROR_DEVICE_LOST] = "VK_ERROR_DEVICE_LOST";
		map[VK_ERROR_MEMORY_MAP_FAILED] = "VK_ERROR_MEMORY_MAP_FAILED";
		map[VK_ERROR_LAYER_NOT_PRESENT] = "VK_ERROR_LAYER_NOT_PRESENT";
		map[VK_ERROR_EXTENSION_NOT_PRESENT] = "VK_ERROR_EXTENSION_NOT_PRESENT";
		map[VK_ERROR_FEATURE_NOT_PRESENT] = "VK_ERROR_FEATURE_NOT_PRESENT";
		map[VK_ERROR_INCOMPATIBLE_DRIVER] = "VK_ERROR_INCOMPATIBLE_DRIVER";
		map[VK_ERROR_TOO_MANY_OBJECTS] = "VK_ERROR_TOO_MANY_OBJECTS";
		map[VK_ERROR_FORMAT_NOT_SUPPORTED] = "VK_ERROR_FORMAT_NOT_SUPPORTED";
		map[VK_ERROR_FRAGMENTED_POOL] = "VK_ERROR_FRAGMENTED_POOL";
		map[VK_ERROR_SURFACE_LOST_KHR] = "VK_ERROR_SURFACE_LOST_KHR";
		map[VK_ERROR_NATIVE_WINDOW_IN_USE_KHR] = "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR";
		map[VK_SUBOPTIMAL_KHR] = "VK_SUBOPTIMAL_KHR";
		map[VK_ERROR_OUT_OF_DATE_KHR] = "VK_ERROR_OUT_OF_DATE_KHR";
		map[VK_ERROR_INCOMPATIBLE_DISPLAY_KHR] = "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR";
		map[VK_ERROR_VALIDATION_FAILED_EXT] = "VK_ERROR_VALIDATION_FAILED_EXT";
		map[VK_ERROR_INVALID_SHADER_NV] = "VK_ERROR_INVALID_SHADER_NV";
		map[VK_ERROR_OUT_OF_POOL_MEMORY_KHR] = "VK_ERROR_OUT_OF_POOL_MEMORY_KHR";
		map[VK_ERROR_INVALID_EXTERNAL_HANDLE_KHR] = "VK_ERROR_INVALID_EXTERNAL_HANDLE_KHX";
		map[VK_RESULT_MAX_ENUM] = "VK_RESULT_MAX_ENUM";
	}
	return map[result];
}

