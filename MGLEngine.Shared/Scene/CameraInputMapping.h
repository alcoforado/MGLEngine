#pragma once
#include "CameraController.h"
#include <MGLEngine.Shared/Events/KeyboardSource.h>
#include <MGLengine.Shared/Utils/math.h>
class CameraInputMapping : public EventListener<KeyboardEvent>
{
	CameraController _camController;
public:
	CameraInputMapping(Camera& cam) 
	:_camController(cam) {
		_camController.SetSphericLockMode(glm::vec3(0, 0, 0), 0.5, degToRad(1.0));
		_camController.Emit();
	
	}

	~CameraInputMapping() override {}

	void Process(const KeyboardEvent& ev) override;



};