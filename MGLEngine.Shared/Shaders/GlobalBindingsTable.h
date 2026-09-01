#pragma once
#include <vector>
#include <string>
#include <map>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <vector>
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

class  ResourceBindingBase {
public:
	std::string name;
	unsigned int binding;
	BindedTypeEnum type;
	//std::vector<ResourceAssignments>
	
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

struct ImageRef {
	std::string filePath;
	std::vector<std::string> references;
};

class Sampler2DBinding : public ResourceBindingBase {
public:
	std::vector<ImageRef> imageFiles;
	bool useAtlas;
	virtual bool Compatible(ResourceBindingBase& b1) const override 
	{
		if (ResourceBindingBase::Compatible(b1))
			return useAtlas == dynamic_cast<Sampler2DBinding*>(&b1)->useAtlas;
		return false;
	}
};


struct GlobalIndex {
	unsigned index;
	BindedTypeEnum type;
};

class ShaderBindingManager;
class GlobalBindingsTable
{
private:
	bool CheckCollisionAndThrowErrorIfIncompatible(ResourceBindingBase& bd1);
	ResourceBindingBase& _GetResourceBinding(GlobalIndex index);
	friend class ShaderBindingManager;


	std::map<std::string, GlobalIndex> _name_index;
	std::map<unsigned int, GlobalIndex> _binding_index;
	std::vector<Sampler2DBinding> _vSampler2DBindings;
	const ResourceBindingBase& GetResourceBinding(GlobalIndex index);
	
public:
	const ResourceBindingBase& GetResourceBinding(GlobalIndex index) const;
	void AddSampler2D(unsigned binding, std::string name,std::string shaderReference);
	void AssignImageResource(std::string bindName, std::string filePath, std::string sourceReference);
	
	const std::vector<Sampler2DBinding> GetSampler2DBindings() const {
		return _vSampler2DBindings;
	}

	

};