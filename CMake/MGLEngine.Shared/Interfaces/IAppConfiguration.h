#pragma once
#include <string>
#include <MGLEngine.Shared/Interfaces/IShader.h>
class IAppConfiguration
{
public:
	virtual void EnableDebugLayer(bool flag) = 0;
	virtual void AppName(std::string name) = 0;
	virtual void AddShader(std::string id, IShader* pShader) = 0;
	virtual void SetDoubleBuffer() = 0;
	virtual void SetTrippleBuffer() = 0;
	virtual void EnableVSync(bool flag) = 0;

};