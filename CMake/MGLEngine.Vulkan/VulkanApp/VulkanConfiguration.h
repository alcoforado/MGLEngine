#include <string>
#include <unordered_map>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IAppConfiguration.h>
class VulkanConfiguration : public IAppConfiguration{

public:
	std::string Name;
	std::unordered_map<std::string, IShader*> Shaders;
	bool EnableDebug=false;
	unsigned SwapChainSize=0; //number of images buffers in the swap chain
	bool VSync=true;
public:
	virtual void EnableDebugLayer(bool flag) { EnableDebug = flag; }
	virtual void AppName(std::string name) { Name = name; }
	virtual void AddShader(std::string id, IShader* pShader) { Shaders[id] = pShader; }
	virtual void SetDoubleBuffer() { SwapChainSize = 2; }
	virtual void SetTrippleBuffer() { SwapChainSize = 3; }
	virtual void EnableVSync(bool flag) { VSync = flag; }

};