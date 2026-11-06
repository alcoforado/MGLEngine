#pragma once
#include <string>
#include <map>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <typeinfo>
#include <typeindex>
#include <memory>
#include <MGLEngine.Shared/Utils/eassert.h>


class IAppConfiguration {
public:
	virtual void EnableDebugLayer(bool flag) = 0;
	virtual void AppName(std::string name) = 0;
	virtual void ImagesRoot(std::string imageRootPath)=0;
	virtual void SetDoubleBuffer() = 0;
	virtual void SetTrippleBuffer() = 0;
	virtual void EnableVSync(bool flag) = 0;
	virtual void SetVersion(unsigned int major, unsigned int minor, unsigned int patch) = 0;
};

class AppConfiguration : public IAppConfiguration {

public:
	bool depthBufferRequested = false;
	std::string Name;
	std::string AssetsRootPath;
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
	void EnableDebugLayer(bool flag) override { EnableDebug = flag; }
	void AppName(std::string name) override { Name = name; }
	void ImagesRoot(std::string imageRootPath) override;
	void SetDoubleBuffer() override { SwapChainSize = 2; }
	void SetTrippleBuffer() override { SwapChainSize = 3; }
	void EnableVSync(bool flag) override { VSync = flag; }
	void SetVersion(unsigned int major, unsigned int minor, unsigned int patch) override { MajorVersion = major; MinorVersion = minor; PatchVersion = patch; }
};