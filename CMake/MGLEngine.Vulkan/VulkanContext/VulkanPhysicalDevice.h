#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanLayerProperties.h"
#include "VulkanLogicalDevice.h"
#include <glfw/glfw3.h>
#include "VulkanMemoryProperties.h"
#include <functional>

class VulkanInstance;

struct VulkanQueueFamily {
	uint32_t	queueFlags;
	uint32_t    numberOfQueues;
	uint32_t    timestampValidBits;
	uint32_t    index;
	VkExtent3D  minImageTransferGranularity;
	bool IsGraphic;
	bool IsCompute;
	bool IsTransfer;
	bool IsSparseBinding;
	bool IsProtected;
	bool IsVideoDecode;
	bool IsVideoEncode;
	bool IsOpticalFlow;
	bool IsDataGraph;
	bool HasMaxGranularity() {
		return minImageTransferGranularity.width == minImageTransferGranularity.height == 	minImageTransferGranularity.depth == 1;
	}


};


class VulkanPhysicalDevice {

	friend VulkanInstance;


	const VulkanInstance& _vulkanInstance;
	std::vector<VulkanMemoryProperties> _memProperties;
	std::vector<VulkanQueueFamily> _queueFamilies;
	VkPhysicalDevice _handler;
	
	VkPhysicalDeviceFeatures _features;
	VkPhysicalDeviceProperties _graphicProperties;
	std::vector<MVulkanLayer> _layers;
	int32_t _graphic_family_index;
	private:
		void ComputeMemoryProperties();
		void ComputeFamilyQueues();
		void ComputeLayers();
		VulkanPhysicalDevice(const VulkanInstance& inst, VkPhysicalDevice handler);
public:
	const VulkanInstance& GetVulkanInstance() const { return _vulkanInstance; }
	VkPhysicalDevice GetHandle() const  { return _handler; }
	const std::vector<VulkanQueueFamily>& GetQueueFamilies() const { return _queueFamilies; }
	VkPhysicalDeviceProperties GetProperties() const { return _graphicProperties; }
	VulkanLogicalDevice* CreateLogicalDevice(GLFWwindow *window) const;
	std::vector<VulkanMemoryProperties> GetMemoryProperties() const { return _memProperties; }
	int32_t FindQueueFamilyIndex(std::function<bool(const VulkanQueueFamily& family)> selector) const;
	int32_t FindMemoryPropertyIndex(std::function<bool(const VulkanMemoryProperties& memory)> selector) const;
	int32_t GetGraphicFamilyQueueIndex() const {return _graphic_family_index;}
	bool IsDiscrete() const;
	bool IsIntegrated() const;
	bool IsCPU() const;
	bool IsVirtual() const;
	bool HasGhraphicsQueue() const;
	bool HasComputeQueue() const;
	VkSurfaceCapabilitiesKHR GetCapabilitiesForSurface(VulkanSurface& surface) const;
	std::vector<VkSurfaceFormatKHR> GetCompatibleSurfaceFormats(VulkanSurface& surface) const





};

