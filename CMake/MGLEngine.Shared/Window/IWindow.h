#pragma once
class IWindowEventHandler;
class ICanvas;
class ShapesService;
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
	virtual void AttachEventHandler(IWindowEventHandler *eh)=0;
	virtual void DetachEventHandler(IWindowEventHandler *eb)=0;
	virtual ICanvas* GetCanvas() = 0;
	virtual ShapesService* GetShapesManager() = 0;
	virtual ~IWindow()
	{
	}
};

