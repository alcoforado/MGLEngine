#include "GlobalBindingsTable.h"
#include <MGLEngine.Shared/Utils/eassert.h>
std::map<std::string, ResourceBinding> GlobalBindingsTable::_globalBindings;


void GlobalBindingsTable::AddSampler2D(unsigned binding, std::string name)
{
	ResourceBinding  bd;
	bd.binding = binding;
	bd.name = name;
	bd.type = BindedTypeEnum::SAMPLER_2D;

	eassert(_globalBindings.find(name) == _globalBindings.end(), std::format("Error binding {} already exists", name));
		_globalBindings[name] = bd;
}

void GlobalBindingsTable::FillOutGlobalBinding()
{
	//Texture2D
	AddSampler2D(1, "sampler");
	

}
