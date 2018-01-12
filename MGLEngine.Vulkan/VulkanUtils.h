#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <fstream>
#include  <vector>
#include <algorithm>
void AssertVulkanSuccess(VkResult res);

std::string MapVkResultToString(VkResult result);

extern std::ofstream vulkanError;

std::vector<std::string> ConvertToVectorString(std::vector<const char*> user);

std::vector<const char*> ConvertToVectorChar(const std::vector<std::string>& user);

template<class T>
std::vector<T> Concat(const std::vector<T> &a,const std::vector<T> &b)
{
	std::vector<T> ret();
	copy(a.begin(), a.end(), back_inserter(ret));
	copy(b.begin(), b.end(), back_inserter(ret));
	return ret;
}


template<class T>
int FromBitFlagsToInt(const std::vector<T> v)
{
	int r = 0;
	for (T e : v)
	{
		r |= e;
	}
	return r;
}