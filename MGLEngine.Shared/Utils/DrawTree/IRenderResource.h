#pragma once
class IRenderResource
{
public:
	virtual bool Compatible(IRenderResource *res) = 0;
	virtual ~IRenderResource() = 0;
};