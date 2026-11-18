#pragma once
#include "Camera.h"

struct SphericCoordinate
{
	
	double dr;
	double dPhi;
	double cos_dphi;
	double sin_dphi;
	glm::dvec3 lockPoint;
};


class CameraController
{
	SphericCoordinate _sphere;
	Camera& _camera;
public:
	CameraController(Camera& cam)
		:_camera(cam)
	{
		
		
	}
	
	void SetSphericLockMode(glm::vec3 pointLock, float dr, float dPhi)
	{
		_sphere.cos_dphi = cos(dPhi);
		_sphere.sin_dphi = sin(dPhi);
		_sphere.dr = dr;
		_sphere.dPhi = dPhi;
		_sphere.lockPoint = pointLock;
		_camera.SetCamera(_camera.Pos(), pointLock, glm::vec3(0, 0, 1));
	}

	
	void SphericGoNear()
	{
		_camera._pos = _camera._pos + _camera._depth * _sphere.dr;
	}

	void SphericGoFar()
	{
		_camera._pos = _camera._pos - _camera._depth * _sphere.dr;
	}

	void SphericGoDown()
	{
		//set 
		auto pos  = _camera._pos-_sphere.lockPoint; //origin translation to lockPoint
		double rxy = hypot(pos.x, pos.y);
		if (rxy < 0.00001*fabs(pos.z))
			return;
		_camera._pos.z = pos.z * _sphere.cos_dphi - rxy * _sphere.sin_dphi;
		double aux = (_sphere.cos_dphi + pos.z * _sphere.sin_dphi / rxy);
		_camera._pos.y = aux * pos.y;
		_camera._pos.x = aux * pos.x;
		glm::dvec3 up = glm::vec3(0, 0, 1);
		_camera._depth = -glm::normalize(_camera._pos);
		_camera._down = -up + _camera._depth * glm::dot(up, _camera._depth); // - (up - _depth*dot(_depth,up)
		_camera._down = glm::normalize(_camera._down);
		_camera._pos += _sphere.lockPoint;
		_camera.GetProjection();
	}

	void SphericGoUp() {
		auto pos = _camera._pos -_sphere.lockPoint; //origin translation to lockPoint
		double rxy = hypot(pos.x, pos.y);
		if (rxy < 0.00001 * fabs(pos.z))
			return;

		_camera._pos.z = pos.z * _sphere.cos_dphi + rxy * _sphere.sin_dphi;
		double aux = (_sphere.cos_dphi - pos.z * _sphere.sin_dphi / rxy);
		_camera._pos.y = aux * pos.y;
		_camera._pos.x = aux * pos.x;

		glm::dvec3 up = glm::vec3(0, 0, 1);
		_camera._depth = -glm::normalize(_camera._pos);
		_camera._down = -up + _camera._depth * glm::dot(up, _camera._depth); // - (up - _depth*dot(_depth,up)
		_camera._down = glm::normalize(_camera._down);
		_camera._pos += _sphere.lockPoint;
		_camera.GetProjection();
	}

	void SphericGoRight()
	{
		auto pos = _camera._pos - _sphere.lockPoint; //origin translation to lockPoint
		glm::dvec3 result;
		result.z = pos.z;
		result.x = pos.x * _sphere.cos_dphi - pos.y * _sphere.sin_dphi;
		result.y = pos.x * _sphere.sin_dphi + pos.y * _sphere.cos_dphi;
		_camera._pos = result + _sphere.lockPoint;
		
		//depth
		result.z = _camera._depth.z;
		result.x = _camera._depth.x*_sphere.cos_dphi - _camera._depth.y * _sphere.sin_dphi;
		result.y = _camera._depth.x*_sphere.sin_dphi + _camera._depth.y * _sphere.cos_dphi;
		_camera._depth = result;
		
		//down
		result.z = _camera._down.z;
		result.x = _camera._down.x * _sphere.cos_dphi - _camera._down.y * _sphere.sin_dphi;
		result.y = _camera._down.x * _sphere.sin_dphi + _camera._down.y * _sphere.cos_dphi;
		_camera._down = result;

		//right
		result.z = _camera._right.z;
		result.x = _camera._right.x * _sphere.cos_dphi - _camera._right.y * _sphere.sin_dphi;
		result.y = _camera._right.x * _sphere.sin_dphi + _camera._right.y * _sphere.cos_dphi;
		_camera._right = result;

		_camera.GetProjection();

	}


	void SphericGoLeft()
	{
		auto pos = _camera._pos - _sphere.lockPoint; //origin translation to lockPoint
		glm::dvec3 result;
		result.z = pos.z;
		result.x = pos.x * _sphere.cos_dphi + pos.y * _sphere.sin_dphi;
		result.y =-pos.x * _sphere.sin_dphi + pos.y * _sphere.cos_dphi;
		_camera._pos = result + _sphere.lockPoint;

		//depth
		result.z = _camera._depth.z;
		result.x = _camera._depth.x * _sphere.cos_dphi + _camera._depth.y * _sphere.sin_dphi;
		result.y =-_camera._depth.x * _sphere.sin_dphi + _camera._depth.y * _sphere.cos_dphi;
		_camera._depth = result;

		//down
		result.z = _camera._down.z;
		result.x = _camera._down.x * _sphere.cos_dphi + _camera._down.y * _sphere.sin_dphi;
		result.y =-_camera._down.x * _sphere.sin_dphi + _camera._down.y * _sphere.cos_dphi;
		_camera._down = result;

		//right
		result.z = _camera._right.z;
		result.x = _camera._right.x * _sphere.cos_dphi + _camera._right.y * _sphere.sin_dphi;
		result.y =-_camera._right.x * _sphere.sin_dphi + _camera._right.y * _sphere.cos_dphi;
		_camera._right = result;

		_camera.GetProjection();

	}

	void Emit() {
		_camera.Emit();
	}


};