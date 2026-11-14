#pragma once
#include "EventSource.h"

struct KeyboardEvent {
	int key;
	int scancode;
	int action;
	int mods;


};

class KeyboardSource : public EventSource<KeyboardEvent>
{
private:
	size_t count = 0;
public:
	void Emit() {
		auto ev = KeyboardEvent{
			
		};
		this->EmitEvent(ev);
	}

}; 