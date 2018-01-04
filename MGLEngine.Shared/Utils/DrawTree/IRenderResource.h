#pragma once
class IRenderResource
{
	virtual bool Compatible(IRenderResource *res) = 0;
	virtual ~IRenderResource() = 0;
};