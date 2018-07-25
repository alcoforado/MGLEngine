#pragma once
class IVulkanSlotBinding
{
public:
	IVulkanSlotBinding();
	~IVulkanSlotBinding();

	virtual bool NeedUpdate()=0;
	virtual void Update()=0;
};

