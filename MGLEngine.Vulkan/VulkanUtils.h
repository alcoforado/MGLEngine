#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
void AssertVulkanSuccess(VkResult res);

std::string MapVkResultToString(VkResult result);

extern std::ofstream vulkanError;

