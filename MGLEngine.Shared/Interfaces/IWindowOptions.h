#pragma once
#include <string>

class IWindowOptions {
public:
	virtual void SetSize(int width, int height) = 0;
	virtual void SetFullScreen() = 0;
	virtual void SetTitle(const std::string& str) = 0;
};

class  WindowOptions : public IWindowOptions {
public:
	int Height = 800;
	int Width = 800;
	bool FullScreen = false;
	std::string Title;
public:
	virtual void SetSize(int width, int height) { Height = height; Width = width; }
	virtual void SetFullScreen() { FullScreen = true; }
	virtual void SetTitle(const std::string& str) { Title = str; }

};

