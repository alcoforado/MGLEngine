#pragma once
#include <glm/glm.hpp>
#include <MGLEngine.Shared/Events/EventSource.h>
class CameraController;
class Camera 
{
friend class CameraController;
private:
	glm::dvec3 _down, _right, _depth,_pos;
	double _theta, _alpha, _n, _f;
	glm::mat4 _NdcProj;
	glm::mat4 _PerspectiveProjection;

	EventSource<glm::mat4> _NdcProjectionEmitter;

public:

	Camera(float cameraLensTotalAngle, float x_yRatio, float nearClipPlane, float farClipPlane);
	Camera();
	void SetCamera(glm::dvec3 pos, glm::dvec3 ptToLookAt, glm::dvec3 up);
	void Resize(float x_yRatio);
	void SetLens(double cameraLensTotalAngle, double x_yRatio, double nearClipPlane, double farClipPlane);
	const glm::mat4& GetProjection();
	void Emit();
	const glm::vec3& Pos() { return _pos; }
	const glm::vec3& LookAt() { return _depth; }
	IObservable<glm::mat4>& GetEmitter() { return _NdcProjectionEmitter; }


};