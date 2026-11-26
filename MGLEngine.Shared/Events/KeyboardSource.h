#pragma once
#include "EventSource.h"

class KeyboardEvent {
public:
	int key;
	int scancode;
	int action;
	int mods;
public:
	bool KeyPressed() const;
	bool KeyReleased() const;

};

class KeyboardSource : public EventSource<KeyboardEvent>
{
private:
	size_t count = 0;
public:
	
}; 