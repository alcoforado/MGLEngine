#pragma once
#include <vector>
#include <string>
#include <map>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include "GlobalBindings.h"





struct GlobalIndex {
	size_t index;
	BindedTypeEnum type;

	bool IsSampler() {
		return type == BindedTypeEnum::SAMPLER_2D;
	}
};

class GlobalBindingsTable
{
private:
	bool CheckCollisionAndThrowErrorIfIncompatible(ResourceBindingBase& bd1);
	ResourceBindingBase& _GetResourceBinding(GlobalIndex index);


	std::map<std::string, GlobalIndex> _name_index;
	std::map<unsigned int, GlobalIndex> _binding_index;
	std::vector<Sampler2DBinding> _vSampler2DBindings;
	const ResourceBindingBase& GetResourceBinding(GlobalIndex index);
	
public:
	const ResourceBindingBase& GetResourceBinding(GlobalIndex index) const;
	const Sampler2DBinding& GetSampler(std::string name);
	void AddSampler2D(unsigned binding, std::string name,std::string shaderReference);
	void AssignImageResource(std::string bindName, const ResourceDeclaration& config,ShaderRef& sourceReference);
	GlobalIndex GetResourceByName(std::string name)   { return _name_index[name]; }
	size_t NBindings() const { return _name_index.size(); }
	std::vector<Sampler2DBinding>& GetSampler2DBindings()  {
		return _vSampler2DBindings;
	}

	

};