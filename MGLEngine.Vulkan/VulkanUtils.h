#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include  <vector>
void AssertVulkanSuccess(VkResult res);

std::string MapVkResultToString(VkResult result);

extern std::ofstream vulkanError;

std::vector<std::string> ConvertToVectorString(std::vector<const char*> user);

std::vector<const char*> ConvertToVectorChar(std::vector<std::string> user);
