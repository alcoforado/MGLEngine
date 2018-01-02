#pragma once
class IResource
{
	virtual bool Compatible(IResource *res) = 0;
	virtual ~IResource() = 0;
};