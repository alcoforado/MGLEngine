#pragma once

#include "Light.h"

class Scene {

	std::vector<Light> _lights;
public:
	void SetLights(std::vector<Light> lights)
	{
		_lights = lights;
	}



};