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
		unsigned int newBindingIndex = _vSampler2DBindings.size() - 1;
		GlobalIndex gi = {
			.index = newBindingIndex,
			.type = BindedTypeEnum::SAMPLER_2D
		};
		_binding_index[binding] = _name_index[name] = gi;

	}




}
void GlobalBindingsTable::AssignImageResource(std::string bindName, std::string filePath)
{
	if (_name_index.contains(bindName))
	{
		auto ref = _name_index[bindName];
		switch (ref.type)
		{
		case BindedTypeEnum::SAMPLER_2D:
		{
			auto& sampler2DBinding = _vSampler2DBindings[ref.index];
			if (sampler2DBinding.imageFiles.empty() || sampler2DBinding.useAtlas)
			{
				sampler2DBinding.imageFiles.insert(filePath);
			}
			else {
				throw_formatted("Can assign image {} to the Sampler2D {}. It doesn't accept multiple images", filePath, bindName)
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


