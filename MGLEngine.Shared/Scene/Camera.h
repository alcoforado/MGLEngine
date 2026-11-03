#pragma once
#include <glm/glm.hpp>

class Camera
{
	glm::vec3 _down, _right, _depth,_pos;

	glm::mat4 NdcProj;
public:
	Camera(float cameraLensTotalAngle, float x_yRatio, float nearClipPlane, float farClipPlane);
	void SetCamera(glm::vec3 pos, glm::vec3 ptToLookAt, glm::vec3 up);
	
	void GetNdcProjection()

};