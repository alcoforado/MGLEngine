


#pragma once
#include "UniformBufferSlot.h"

class UniformSlotBinding
{
	bool _needsUpdate;
	
public:
	void Update();
	bool NeedsUpdate();
	UniformSlotBinding();
	~UniformSlotBinding();
};

