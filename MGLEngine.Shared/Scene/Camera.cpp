#include "Camera.h"
#include <cmath>
Camera::Camera()
{
	this->SetLens(0.6109f, 1.0f, 0.5f, 1000.0f);
}


Camera::Camera(float cameraLensTotalAngleRad, float y_xRatio, float nearClipPlane, float farClipPlane)
{
	this->SetLens(cameraLensTotalAngleRad, y_xRatio, nearClipPlane, farClipPlane);
}


void Camera::SetLens(double cameraLensTotalAngleRad, double y_xRatio, double nearClipPlane, double farClipPlane)
{
	_theta = cameraLensTotalAngleRad;
	_alpha = y_xRatio;
	_n = nearClipPlane;
	_f = farClipPlane;

	double tan_theta_2 = tan(_theta / 2.0);


	glm::mat4 PerspectiveProjectionTranspose( //row vec4
		glm::vec4(1.0/(tan_theta_2*_alpha)	,			0		,		0		,		0		),
		glm::vec4(			0				, 1.0 / tan_theta_2	,		0		,		0		),
		glm::vec4(			0				,			0		,	_f/(_f-_n)	, -_f*_n/(_f-_n)),
		glm::vec4(			0				,			0		,		1		,		0		)
	);

	_PerspectiveProjection = glm::transpose(PerspectiveProjectionTranspose);
}



void Camera::Resize(float x_yRatio)
{
	this->SetLens(_theta, x_yRatio, _n, _f);
}



void Camera::SetCamera(glm::dvec3 pos, glm::dvec3 ptToLookAt, glm::dvec3 up)
{
	_pos  = pos;
	_depth= glm::normalize(ptToLookAt - pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_right= glm::cross(_down, _depth);


	GetProjection();


}

void Camera::Emit() {
	_NdcProjectionEmitter.EmitEvent(_NdcProj);
}


const glm::mat4& Camera::GetProjection()
{
	auto ViewTransform = glm::mat4(//columnorder
		glm::vec4(_right.x, _down.x, _depth.x, 0),
		glm::vec4(_right.y, _down.y, _depth.y, 0),
		glm::vec4(_right.z, _down.z, _depth.z, 0),
		glm::vec4(-glm::dot(_right, _pos), -glm::dot(_down, _pos), -glm::dot(_depth, _pos), 1)
	);

	_NdcProj = _PerspectiveProjection * ViewTransform;

	return _NdcProj;



}




void Camera::SetSphericLockMode(glm::vec3 pointLock, float dr, float dPhi)
{
	_sphere.cos_dphi = cos(dPhi);
	_sphere.sin_dphi = sin(dPhi);
	_sphere.dr = dr;
	_sphere.dPhi = dPhi;
	_sphere.lockPoint = pointLock;
	SetCamera(Pos(), pointLock, glm::vec3(0, 0, 1));
}


void Camera::SphericGoNear()
{
	_pos = _pos + _depth * _sphere.dr;
	GetProjection();
}

void Camera::SphericGoFar()
{
	_pos = _pos - _depth * _sphere.dr;
	GetProjection();
}

void Camera::SphericGoDown()
{
	auto pos  = _pos-_sphere.lockPoint; //origin translation to lockPoint
	double rxy = hypot(pos.x, pos.y);
	if (rxy < 0.00001*fabs(pos.z))
		return;
	double aux = (_sphere.cos_dphi + pos.z * _sphere.sin_dphi / rxy);
	if (aux < 0)
		return;
	_pos.z = pos.z * _sphere.cos_dphi - rxy * _sphere.sin_dphi;
	_pos.y = aux * pos.y;
	_pos.x = aux * pos.x;
	glm::dvec3 up = glm::vec3(0, 0, 1);
	_depth = -glm::normalize(_pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_pos += _sphere.lockPoint;
	GetProjection();
}

void Camera::SphericGoUp() {
	auto pos = _pos -_sphere.lockPoint; //origin translation to lockPoint
	double rxy = hypot(pos.x, pos.y);
	if (rxy < 0.00001 * fabs(pos.z))
		return;
	double aux = (_sphere.cos_dphi - pos.z * _sphere.sin_dphi / rxy);
	if (aux < 0)
		return;
	_pos.z = pos.z * _sphere.cos_dphi + rxy * _sphere.sin_dphi;
	_pos.y = aux * pos.y;
	_pos.x = aux * pos.x;

	glm::dvec3 up = glm::vec3(0, 0, 1);
	_depth = -glm::normalize(_pos);
	_down = -up + _depth * glm::dot(up, _depth); // - (up - _depth*dot(_depth,up)
	_down = glm::normalize(_down);
	_pos += _sphere.lockPoint;
	GetProjection();
}

void Camera::SphericGoRight()
{
	auto pos = _pos - _sphere.lockPoint; //origin translation to lockPoint
	glm::dvec3 result;
	result.z = pos.z;
	result.x = pos.x * _sphere.cos_dphi - pos.y * _sphere.sin_dphi;
	result.y = pos.x * _sphere.sin_dphi + pos.y * _sphere.cos_dphi;
	_pos = result + _sphere.lockPoint;

	//depth
	result.z = _depth.z;
	result.x = _depth.x*_sphere.cos_dphi - _depth.y * _sphere.sin_dphi;
	result.y = _depth.x*_sphere.sin_dphi + _depth.y * _sphere.cos_dphi;
	_depth = result;

	//down
	result.z = _down.z;
	result.x = _down.x * _sphere.cos_dphi - _down.y * _sphere.sin_dphi;
	result.y = _down.x * _sphere.sin_dphi + _down.y * _sphere.cos_dphi;
	_down = result;

	//right
	result.z = _right.z;
	result.x = _right.x * _sphere.cos_dphi - _right.y * _sphere.sin_dphi;
	result.y = _right.x * _sphere.sin_dphi + _right.y * _sphere.cos_dphi;
	_right = result;

	GetProjection();

}


void Camera::SphericGoLeft()
{
	auto pos = _pos - _sphere.lockPoint; //origin translation to lockPoint
	glm::dvec3 result;
	result.z = pos.z;
	result.x = pos.x * _sphere.cos_dphi + pos.y * _sphere.sin_dphi;
	result.y =-pos.x * _sphere.sin_dphi + pos.y * _sphere.cos_dphi;
	_pos = result + _sphere.lockPoint;

	//depth
	result.z = _depth.z;
	result.x = _depth.x * _sphere.cos_dphi + _depth.y * _sphere.sin_dphi;
	result.y =-_depth.x * _sphere.sin_dphi + _depth.y * _sphere.cos_dphi;
	_depth = result;

	//down
	result.z = _down.z;
	result.x = _down.x * _sphere.cos_dphi + _down.y * _sphere.sin_dphi;
	result.y =-_down.x * _sphere.sin_dphi + _down.y * _sphere.cos_dphi;
	_down = result;

	//right
	result.z = _right.z;
	result.x = _right.x * _sphere.cos_dphi + _right.y * _sphere.sin_dphi;
	result.y =-_right.x * _sphere.sin_dphi + _right.y * _sphere.cos_dphi;
	_right = result;

	GetProjection();

}

