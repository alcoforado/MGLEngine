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
		_camera.SphericGoFar();
		break;
	case GLFW_KEY_ENTER:
		_camera.SphericGoNear();
		break;
	case GLFW_KEY_DOWN:
		_camera.SphericGoDown();
		break;
	case GLFW_KEY_UP:
		_camera.SphericGoUp();
		break;
	case GLFW_KEY_LEFT:
		_camera.SphericGoLeft();
		break;
	case GLFW_KEY_RIGHT:
		_camera.SphericGoRight();
		break;
	default:
		return;

	}
	_camera.Emit();
	
}
