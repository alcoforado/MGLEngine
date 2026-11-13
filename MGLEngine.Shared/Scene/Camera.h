#pragma once
#include <glm/glm.hpp>
#include <MGLEngine.Shared/Events/EventSource.h>

class Camera 
{
private:
	glm::vec3 _down, _right, _depth,_pos;
	float _theta, _alpha, _n, _f;
	glm::mat4 _NdcProj;
	glm::mat4 _PerspectiveProjection;

	EventSource<glm::mat4> _NdcProjectionEmitter;

public:

	Camera(float cameraLensTotalAngle, float x_yRatio, float nearClipPlane, float farClipPlane);
	Camera();
	void SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up);
	void Resize(float x_yRatio);
	void SetLens(float cameraLensTotalAngle, float x_yRatio, float nearClipPlane, float farClipPlane);
	const glm::mat4& GetProjection();
	void Emit();
	IObservable<glm::mat4>& GetEmitter() { return _NdcProjectionEmitter; }


};