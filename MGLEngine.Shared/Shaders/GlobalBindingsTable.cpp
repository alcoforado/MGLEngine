#pragma once
#include "GlobalBindingsTable.h"
#include <MGLEngine.Shared/Utils/eassert.h>
#include <format>

void GlobalBindingsTable::AddSampler2D(unsigned binding, std::string name,std::string reference)
{
	ResourceBinding  bd;
	bd.binding = binding;
	bd.name = name;
	bd.type = BindedTypeEnum::SAMPLER_2D;
	bd.references.push_back(reference);


	//validation to make sure different shaders don't declare the same binding for different resources
	if (_name_index.contains(name))
	{
		CheckCollision(_vBindings[_name_index[name]], bd); //trhow error if collision
		_vBindings[_name_index[name]].references.push_back(reference); //Just add the one more reference
		return;
	}
	if (_binding_index.contains(binding))
	{
		CheckCollision(_vBindings[_binding_index[binding]], bd);
		_vBindings[_binding_index[binding]].references.push_back(reference); //Just add the one more reference
		return;
	}

	_vBindings.push_back(bd);
	//Updated indices
	unsigned int newBindingIndex = _vBindings.size() - 1;
	_binding_index[binding]=_name_index[name] = newBindingIndex; 
	


}

void GlobalBindingsTable::CheckCollision(ResourceBinding& bd1, ResourceBinding& bd2)
{
	if (bd1.type == bd2.type && bd1.name == bd2.name && bd1.binding == bd2.binding)
	{
		return;
	}
	else
		throw_error(std::format("Binding Definition Collision For {} {}",bd1.ToString(),bd2.ToString()));

}


