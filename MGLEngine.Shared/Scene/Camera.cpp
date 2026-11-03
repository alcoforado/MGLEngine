#include "Camera.h"

void Camera::SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up)
{
	_pos = pos;
	_depth = glm::normalize(ptToLookAt - pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_right = glm::cross(_down, _depth);

	
}