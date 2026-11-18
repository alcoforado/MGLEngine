#pragma once
#define _USE_MATH_DEFINES 
#include <math.h>


float degToRad(float deg)
{
	return static_cast<float>(deg * 2 * M_PI / 360.0);
}