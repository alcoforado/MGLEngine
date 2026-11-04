#pragma once
#include <glm/glm.hpp>

class Camera
{
	glm::vec3 _down, _right, _depth,_pos;
	float _theta, _alpha, _n, _f;
	glm::mat4 NdcProj;
	glm::mat4 _PerspectiveProjection;
public:
	Camera(float cameraLensTotalAngle, float x_yRatio, float nearClipPlane, float farClipPlane);
	void SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up);
	
	const glm::mat4& GetProjection();

};