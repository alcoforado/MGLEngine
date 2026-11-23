#pragma once
#include "CameraInputMapping.h"
#include <GLFW/glfw3.h>
void CameraInputMapping::ProcessKey(const KeyboardEvent& ev)
{
	if (ev.KeyReleased())
	{
		if (this->key == ev.key)
			tickSubscription->Pause();
		return;
	}
	if (!ev.KeyPressed())
		return;
	switch (ev.key)
	{
	case GLFW_KEY_SPACE:
		[[fallthrough]];
	case GLFW_KEY_ENTER:
		[[fallthrough]];
	case GLFW_KEY_DOWN:
		[[fallthrough]];
	case GLFW_KEY_UP:
		[[fallthrough]];
	case GLFW_KEY_LEFT:
		[[fallthrough]];
	case GLFW_KEY_RIGHT:
		this->key = ev.key;
		tickSubscription->Resume();
		return;
	default:
		return;
	}
	
	
	

	
	
}

void CameraInputMapping::ProcessTick(const TickEvent& ev)
{
	MoveCamera(this->key);
	
}

void CameraInputMapping::MoveCamera(int key) 
{

	switch (key)
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
