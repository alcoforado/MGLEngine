#pragma once
#include "CameraInputMapping.h"
#include <GLFW/glfw3.h>
void CameraInputMapping::Process(const KeyboardEvent& ev)
{
	if (!ev.KeyPressed())
		return;

	switch (ev.key)
	{
	case GLFW_KEY_SPACE:
		_camController.SphericGoFar();
		break;
	case GLFW_KEY_ENTER:
		_camController.SphericGoNear();
		break;
	case GLFW_KEY_DOWN:
		_camController.SphericGoDown();
		break;
	case GLFW_KEY_UP:
		_camController.SphericGoUp();
		break;
	case GLFW_KEY_LEFT:
		_camController.SphericGoLeft();
		break;
	case GLFW_KEY_RIGHT:
		_camController.SphericGoRight();
		break;
	default:
		return;

	}
	_camController.Emit();
	
}
