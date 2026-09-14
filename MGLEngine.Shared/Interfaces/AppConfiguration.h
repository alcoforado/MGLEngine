#pragma once
#include <string>
#include <map>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <MGLEngine.Shared/Utils/eassert.h>

class AppConfiguration {

public:
	std::string Name;
	std::string ImageRootPath;
	bool EnableDebug = false;
	unsigned SwapChainSize = 0; //number of images buffers in the swap chain
	bool VSync = true;
	unsigned int MajorVersion = 1;
	unsigned int MinorVersion = 0;
	unsigned int PatchVersion = 0;
	std::map<std::type_index, IShader*> Shaders;
public:
	const std::map<std::type_index, IShader*>& GetShadersMap() { return Shaders; }
public:
	AppConfiguration();
	virtual void EnableDebugLayer(bool flag) { EnableDebug = flag; }
	virtual void AppName(std::string name) { Name = name; }
	virtual void ImagesRoot(std::string imageRootPath) { ImageRootPath = imageRootPath; }
	virtual void SetDoubleBuffer() { SwapChainSize = 2; }
	virtual void SetTrippleBuffer() { SwapChainSize = 3; }
	virtual void EnableVSync(bool flag) { VSync = flag; }
	virtual void SetVersion(unsigned int major, unsigned int minor, unsigned int patch) { MajorVersion = major; MinorVersion = minor; PatchVersion = patch; }
};