#pragma once
#include <MGLEngine.Shared\Utils\CommitTag.h>
class IVulkanSlotBinding
{
public:
	CommitTag Tag;
	
	
	IVulkanSlotBinding();
	~IVulkanSlotBinding();

	virtual bool NeedUpdate()=0;
	virtual void Update()=0;
};

