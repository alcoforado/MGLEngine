#include <vector>
#include <string>
#include <map>
#include <MGLEngine.Shared/Utils/eassert.h>

enum BindedTypeEnum {
	SAMPLER_2D
};
struct ResourceBinding {
	std::string name;
	unsigned int binding;
	unsigned int sizeInBytes;
	unsigned int structSizeInBytes;
	unsigned int numElements;
	BindedTypeEnum type;

};


class GlobalBindingsTable
{
	static std::map<std::string,ResourceBinding> _globalBindings;

	static void FillOutGlobalBinding();
	static void AddSampler2D(unsigned binding, std::string name);
	
public:
	GlobalBindingsTable() {

	}
	static ResourceBinding GetGlobalBinding(std::string name)
	{
		if (_globalBindings.empty())
		{
			FillOutGlobalBinding();
		}
		auto it = _globalBindings.find(name);
		if (it != _globalBindings.end())
		{
			return it->second;
		}
		eassert(0,std::format("Global Binding for {} not found",name))

	}

	

};