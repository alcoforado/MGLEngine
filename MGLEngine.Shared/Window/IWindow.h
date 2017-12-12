#pragma once
class IWindow
{
public:

	IWindow()
	{
	}

	virtual void SetSize(int width, int height) = 0;
	virtual void EasyRun() = 0;
	virtual void PsychoRun() =0;
	virtual void Redraw() = 0;


	virtual ~IWindow()
	{
	}
};

