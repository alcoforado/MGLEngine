#pragma once
#include "Camera.h"
#include <MGLEngine.Shared/Events/KeyboardSource.h>
#include <MGLEngine.Shared/Events/FrameTickSource.h>

#include <MGLengine.Shared/Utils/math.h>
class CameraInputMapping  
{
	int key;
	FrameTickSource::SubscriptionHandle tickSubscription;
	Camera& _camera;
public:
	CameraInputMapping(Camera& cam,
		KeyboardSource::Observable  &keyObservable,  
		FrameTickSource::Observable &tickObservable) 
	:_camera(cam) {
		_camera.SetSphericLockMode(glm::vec3(0, 0, 0), 0.5, degToRad(1.0));
		_camera.Emit();

		keyObservable.Subscribe([this](const KeyboardEvent& ev) {
			ProcessKey(ev);
		});
		tickSubscription= tickObservable.Subscribe([this](const TickEvent& ev) {
			ProcessTick(ev);
		});
		tickSubscription->Pause();
	}

	~CameraInputMapping()  {}

	void ProcessKey(const KeyboardEvent& ev);

	void ProcessTick(const TickEvent& ev);

    void MoveCamera( int key);

};
