#include "glm_extensions.h"
#include <math.h>
glm::mat2 GLMExtensions::RotateMat2(float rads)
{
	float _sin = sin(rads);
	float _cos = cos(rads);
	glm::mat2 m(
		_cos,_sin, //first column
		-_sin,_cos //second column
	);
	return m;

}