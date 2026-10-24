#pragma once
#include "GlobalBindingsTable.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include <format>

void GlobalBindingsTable::AddSampler2D(unsigned binding, std::string name, std::string reference)
{
	Sampler2DBinding  bd;
	bd.binding = binding;
	bd.name = name;
	bd.type = BindedTypeEnum::SAMPLER_2D;
	bd.references.push_back(reference);


	//validation to make sure different shaders don't declare the same binding for different resources

	bool exists = CheckCollisionAndThrowErrorIfIncompatible(bd);
	if (!exists)
	{
		_vSampler2DBindings.push_back(bd);
		size_t newBindingIndex = _vSampler2DBindings.size() - 1;
		GlobalIndex gi = {
			.index = newBindingIndex,
			.type = BindedTypeEnum::SAMPLER_2D
		};
		_binding_index[binding] = _name_index[name] = gi;

	}




}

void GlobalBindingsTable::AddPushConstant(PushConstantConfig& cnst, std::string shaderId)
{
	PushConstantBinding elem;
	elem.type = BindedTypeEnum::PUSH_CONSTANT;
	elem.typeIndex = cnst.typeIndex;
	elem.binding = cnst.binding;
	elem.name = cnst.name;
	elem.shaderId = shaderId;
	elem.references.push_back(shaderId);
	elem.sizeOfDataType = cnst.size;

	bool exists = CheckCollisionAndThrowErrorIfIncompatible(elem);
	if (!exists)
	{
		_vPushConstants.push_back(elem);
		size_t constantIndex = _vPushConstants.size() - 1;
		GlobalIndex gi = {
			.index = constantIndex,
			.type = BindedTypeEnum::PUSH_CONSTANT
		};
		_binding_index[elem.binding] = _name_index[elem.name] = gi;
	}
}


void GlobalBindingsTable::AssignImageResource(std::string bindName, const ResourceDeclaration& config, ShaderRef& sourceReference)
{
	if (_name_index.contains(bindName))
	{
		auto ref = _name_index[bindName];
		switch (ref.type)
		{
		case BindedTypeEnum::SAMPLER_2D:
		{
			auto& sampler2DBinding = _vSampler2DBindings[ref.index];
			for (auto& resRef : sampler2DBinding.resources)
			{
				if (resRef.config.UniqueId() == config.UniqueId()) //resource already added
				{
					resRef.references.push_back(sourceReference);
					return;
				}
			}
			if (sampler2DBinding.resources.empty() || sampler2DBinding.useAtlas)
			{
				ResourceRef res;
				res.config = config;;
				res.references.push_back(sourceReference);

				sampler2DBinding.resources.push_back(res);
			}
			else {
				throw_formatted("Can't assign image {} to the Sampler2D {}. It doesn't accept multiple images", config.filePath, bindName)
			}
			break;
		}
		default:
			throw_formatted("Error Assigning image to {}. Can't add image to {} type", bindName, to_string(ref.type));
		}
	}
	else
		throw_error(std::format("Binding {} not found", bindName));
};


const ResourceBindingBase& GlobalBindingsTable::GetResourceBinding(GlobalIndex index)
{
	return _GetResourceBinding(index);
}

ResourceBindingBase& GlobalBindingsTable::_GetResourceBinding(GlobalIndex index)
{
	switch (index.type)
	{
	case BindedTypeEnum::SAMPLER_2D:
		return _vSampler2DBindings[index.index];
	default:
		throw_error("type not implemented yet");

	}
}


bool GlobalBindingsTable::CheckCollisionAndThrowErrorIfIncompatible(ResourceBindingBase& newBinding)
{
	bool pass = true;
	bool exists = false;
	if (_name_index.contains(newBinding.name))
	{
		exists = true;
		ResourceBindingBase& oldBinding = this->_GetResourceBinding(_name_index[newBinding.name]);

		if (!oldBinding.Compatible(newBinding))
		{
			throw_error(std::format("Binding Definition Collision For {} {}", newBinding.ToString(), oldBinding.ToString()));
		}
	}
	if (_binding_index.contains(newBinding.binding))
	{

		exists = true;
		ResourceBindingBase& oldBinding = this->_GetResourceBinding(_binding_index[newBinding.binding]);
		if (!oldBinding.Compatible(newBinding))
		{
			throw_error(std::format("Binding Definition Collision For {} {}", newBinding.ToString(), oldBinding.ToString()));
		}
		oldBinding.references.insert(oldBinding.references.end(), newBinding.references.begin(), newBinding.references.end());

	}
	return exists;

}

const Sampler2DBinding& GlobalBindingsTable::GetSampler(std::string name)
{
	auto id = _name_index[name];
	switch (id.type)
	{

		case BindedTypeEnum::SAMPLER_2D:
		{
			return _vSampler2DBindings[id.index];
		}
		default:
			throw_formatted("Error, binding  {} is not a sampler", name);
	}

}


