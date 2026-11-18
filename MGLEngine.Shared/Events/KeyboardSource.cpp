#include "KeyboardSource.h"
#include <GLFW/glfw3.h>
bool KeyboardEvent::KeyPressed() const
{
	return action == GLFW_PRESS;
}