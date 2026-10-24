#pragma once
#include <MGLEngine.Shared/Interfaces/GLID.h>

enum BindedTypeEnum {
	SAMPLER_2D, PUSH_CONSTANT
};



constexpr std::string to_string(BindedTypeEnum e)
{
	switch (e) {
	case SAMPLER_2D:
		return "Sampler2D";
	case PUSH_CONSTANT:
		return "PUSH_CONSTANT";
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
	
	GLID glId;


	std::vector<std::string> references; //information about shaders that use the variable. Excellent for debugging



	std::string ToString() const {
		auto result = std::format("(binding={}) {} {} referenced by ", binding, to_string(type), name);
		for (auto ref : references)
		{
			result += ref + ",";
		}
		result.back() = '.';
		return result;
	}
	virtual bool Compatible(ResourceBindingBase& b1) const
	{
		return name == b1.name && binding == b1.binding && type == b1.type;
	}
	virtual ~ResourceBindingBase() {}
};


class Sampler2DBinding : public ResourceBindingBase {
public:
	bool useAtlas;
	std::vector<ResourceRef> resources;
	virtual ~Sampler2DBinding() {}
};

class PushConstantBinding : public ResourceBindingBase {
public:
	size_t sizeOfDataType;
	size_t typeIndex;
	std::string shaderId;
	virtual ~PushConstantBinding() {}

	virtual bool Compatible(ResourceBindingBase& b1) const
	{
		if (ResourceBindingBase::Compatible(b1))
		{
			PushConstantBinding* pc = dynamic_cast<PushConstantBinding*>(&b1);
			return typeIndex == pc->typeIndex && shaderId == pc->shaderId;
		}
		return false;
	}

};
