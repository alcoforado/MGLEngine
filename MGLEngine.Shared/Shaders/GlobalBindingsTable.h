#pragma once
#include <vector>
#include <string>
#include <map>
#include <MGLEngine.Shared/Utils/eassert.h>

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

struct ResourceBinding {
	std::string name;
	unsigned int binding;
	unsigned int sizeInBytes;
	unsigned int structSizeInBytes;
	unsigned int numElements;
	BindedTypeEnum type;
	std::vector<std::string> references; //information about shaders that use the variable. Excellent for debugging

	std::string ToString() {
		auto result = std::format("(binding={}) {} {} referenced by ",binding,to_string(type), name);
		for (auto ref : references)
		{
			result += ref+",";
		}
		result.back() = '.';
		return result;

	}

};

class ShaderBindingManager;
class GlobalBindingsTable
{
	friend class ShaderBindingManager;


	std::map<std::string,unsigned int> _name_index;
	std::map<unsigned int, unsigned int> _binding_index;
	std::vector<ResourceBinding> _vBindings;
	void AddSampler2D(unsigned binding, std::string name,std::string shaderReference);
	void CheckCollision(ResourceBinding& bd1, ResourceBinding& bd2);
	
public:
	
	

	

};