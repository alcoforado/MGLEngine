#include "Camera.h"

Camera::Camera()
{
	this->SetLens(0.6109, 1, 0.5, 1000);
}


Camera::Camera(float cameraLensTotalAngleRad, float y_xRatio, float nearClipPlane, float farClipPlane)
{
	this->SetLens(cameraLensTotalAngleRad, y_xRatio, nearClipPlane, farClipPlane);
}


void Camera::SetLens(float cameraLensTotalAngleRad, float y_xRatio, float nearClipPlane, float farClipPlane)
{
	_theta = cameraLensTotalAngleRad;
	_alpha = y_xRatio;
	_n = nearClipPlane;
	_f = farClipPlane;

	float tan_theta_2 = tan(_theta / 2.0);


	glm::mat4 PerspectiveProjectionTranspose( //row vec4
		glm::vec4(1.0 / (tan_theta_2 * _alpha), 0, 0, 0),
		glm::vec4(0, 1.0 / tan_theta_2, 0, 0),
		glm::vec4(0, 0, _f / (_f - _n), -_f * _n / (_f - _n)),
		glm::vec4(0, 0, 1, 0)
	);

	_PerspectiveProjection = glm::transpose(PerspectiveProjectionTranspose);
}



void Camera::Resize(float x_yRatio)
{
	this->SetLens(_theta, x_yRatio, _n, _f);
}



void Camera::SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up)
{
	_pos = pos;
	_depth = glm::normalize(ptToLookAt - pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_right = glm::cross(_down, _depth);

	auto& projection = GetProjection();
	_NdcProjectionEmitter.EmitEvent(projection);


}


const glm::mat4& Camera::GetProjection()
{
	auto ViewTransform = glm::mat4(//columnorder
		glm::vec4(_right.x, _down.x, _depth.x, 0),
		glm::vec4(_right.y, _down.y, _depth.y, 0),
		glm::vec4(_right.z, _down.z, _depth.z, 0),
		glm::vec4(-glm::dot(_right, _pos), -glm::dot(_down, _pos), -glm::dot(_depth, _pos), 1)
	);

	NdcProj = _PerspectiveProjection * ViewTransform;

	return NdcProj;



}




