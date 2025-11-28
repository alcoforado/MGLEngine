#pragma once
class VulkanSwapChainOptions
{
public: 
	unsigned NBuffers;
	bool VSync;
public:
	void SetDoubleBuffer() { NBuffers = 2; }
	void SetTrippleBuffer() { NBuffers = 3; }
	void EnableVSync(bool flag) { VSync = flag; }
};