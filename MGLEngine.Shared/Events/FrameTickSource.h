#pragma once

#include "EventSource.h";

class TickEvent {
public:
	size_t tick;
	
};

class FrameTickSource : public EventSource<TickEvent>
{
private:
	size_t count = 0;
public:
	void Emit() {
		auto ev = TickEvent{
			.tick = count++
		};
		this->EmitEvent(ev);
	}

};