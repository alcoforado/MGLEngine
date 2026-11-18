#pragma once
#include "Camera.h"
#include <MGLEngine.Shared/Events/KeyboardSource.h>
#include <MGLengine.Shared/Utils/math.h>
class CameraInputMapping : public EventListener<KeyboardEvent>
{
	Camera& _camera;
public:
	CameraInputMapping(Camera& cam) 
	:_camera(cam) {
		_camera.SetSphericLockMode(glm::vec3(0, 0, 0), 0.5, degToRad(1.0));
		_camera.Emit();
	
	}

	~CameraInputMapping() override {}

	void Process(const KeyboardEvent& ev) override;



};
