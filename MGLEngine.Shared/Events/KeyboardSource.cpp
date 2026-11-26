#include "KeyboardSource.h"
#include <GLFW/glfw3.h>
bool KeyboardEvent::KeyPressed() const
{
	return action == GLFW_PRESS;
}

bool KeyboardEvent::KeyReleased() const {
	return action == GLFW_RELEASE;
}