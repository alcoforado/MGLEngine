#include "Camera.h"

void Camera::SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up)
{
	_pos = pos;
	_depth = glm::normalize(ptToLookAt - pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_right = glm::cross(_down, _depth);


}

const glm::mat4& Camera::GetNdcProjection()
{
	NdcProj = glm::mat4(//columnorder
		glm::vec4(_right.x, _down.x, _depth.x, 0),
		glm::vec4(_right.y, _down.y, _depth.y, 0),
		glm::vec4(_right.z, _down.z, _depth.z, 0),
		glm::vec4(-glm::dot(_right, _pos), -glm::dot(_down, _pos), -glm::dot(_depth, _pos), 1)
	);
	return NdcProj;
}

const 


