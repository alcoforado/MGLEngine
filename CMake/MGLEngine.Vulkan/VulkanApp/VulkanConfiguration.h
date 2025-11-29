#include <string>
#include <unordered_map>
#include <MGLEngine.Shared/Shaders/IShader.h>
class VulkanConfiguration {

public:
	std::string Name;
	std::unordered_map<std::string, IShader*> Shaders;
	bool EnableDebug=false;
	unsigned SwapChainSize=0; //number of images buffers in the swap chain
	bool VSync=true;
public:
	void EnableDebugLayer(bool flag) { EnableDebug = flag; }
	void AppName(std::string name) { Name = name; }
	void AddShader(std::string id, IShader* pShader) { Shaders[id] = pShader; }
	void SetDoubleBuffer() { SwapChainSize = 2; }
	void SetTrippleBuffer() { SwapChainSize = 3; }
	void EnableVSync(bool flag) { VSync = flag; }

};