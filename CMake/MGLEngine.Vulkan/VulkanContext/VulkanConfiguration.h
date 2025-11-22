#include <string>
#include <unordered_map>
#include <MGLEngine.Shared/Shaders/IShader.h>
class VulkanConfiguration {

public:
	std::string Name;
	std::unordered_map<std::string, IShader*> Shaders;
	bool EnableDebug=false;
public:
	void EnableDebugLayer(bool flag) { EnableDebug = flag; }
	void AppName(std::string name) { Name = name; }
	void AddShader(std::string id, IShader* pShader) { Shaders[id] = pShader; }
	

};