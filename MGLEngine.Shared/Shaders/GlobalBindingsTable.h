#pragma once
#include <vector>
#include <string>
#include <map>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Interfaces/GLID.h>


enum BindedTypeEnum {
	SAMPLER_2D
};



constexpr std::string to_string(BindedTypeEnum e)
{
	switch (e) {
		case SAMPLER_2D:
			return "Sampler2D";
		default:
			return "Unknown";
	}
}

struct ResourceAssignments {
	int resourceId;

};

struct ShaderRef {
	std::string name;
	std::size_t index;
};

struct ResourceRef {
public:
	ResourceDeclaration config;
	GLID glId;
	size_t MetadataId;
	std::vector<ShaderRef> references;
	ResourceRef() {

	}
};


class  ResourceBindingBase {
public:
	std::string name;
	unsigned int binding;
	BindedTypeEnum type;
	std::vector<ResourceRef> resources;
	GLID glId;

	
	std::vector<std::string> references; //information about shaders that use the variable. Excellent for debugging



	std::string ToString() const {
		auto result = std::format("(binding={}) {} {} referenced by ",binding,to_string(type), name);
		for (auto ref : references)
		{
			result += ref+",";
		}
		result.back() = '.';
		return result;
	}
	virtual bool Compatible(ResourceBindingBase& b1) const
	{
		return name == b1.name && binding == b1.binding && type == b1.type;
	}
};


class Sampler2DBinding : public ResourceBindingBase {
public:
	bool useAtlas;
	virtual bool Compatible(ResourceBindingBase& b1) const override 
	{
		if (ResourceBindingBase::Compatible(b1))
			return useAtlas == dynamic_cast<Sampler2DBinding*>(&b1)->useAtlas;
		return false;
	}
};


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