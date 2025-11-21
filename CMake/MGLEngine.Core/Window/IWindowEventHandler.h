#pragma once

enum MouseAction {PRESS,RELEASE};
enum MouseButton { BUTTON_RIGHT, BUTTON_LEFT };

struct ClickEvent
{
	bool IsPressed;
	bool IsReleased;
	MouseButton MouseButton;
};


class IWindowEventHandler
{
	public:
		virtual void OnMouseMove(double x, double y) = 0;
		virtual void OnMouseClick(ClickEvent evt) = 0;
		virtual ~IWindowEventHandler() {};
};




