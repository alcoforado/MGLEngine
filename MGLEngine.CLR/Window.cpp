// This is the main DLL file.

#include "stdafx.h"

#include "Window.h"
#include "Canvas.h"
#include "Mappers\Topology2DMapper.h"
#include <MGLEngine.Shared\IMGLEngine.h>
#include <MGLEngine.Shared\Window\IWindowEventHandler.h>
#include <vcclr.h>

class WindowEventHandlerWrapper : public IWindowEventHandler
{
	gcroot<MGLEngineCLR::IMngWindowEventHandler^> _eh;
	gcroot<MGLEngineCLR::MngClickEvent^> _mngEvt = gcnew MGLEngineCLR::MngClickEvent;

public:
	WindowEventHandlerWrapper(gcroot<MGLEngineCLR::IMngWindowEventHandler^> eh)
	{
		_eh = eh;
	}


	virtual void OnMouseMove(double x, double y) override {
		_eh->OnMouseMove(x, y);
	}


	virtual void OnMouseClick(ClickEvent evt) override
	{
		_mngEvt->IsPressed = evt.IsPressed;
		_mngEvt->IsReleased = evt.IsReleased;
		_mngEvt->MouseButton = static_cast<int>(evt.MouseButton) ? MGLEngineCLR::BUTTON_RIGHT : MGLEngineCLR::BUTTON_LEFT;
		_eh->OnMouseClick(_mngEvt);
	}

	virtual ~WindowEventHandlerWrapper()
	{}

};

namespace MGLEngineCLR {

	Window::Window()
	{
		_window = UnmanagedFacade::GetContainer()->CreateWindow();
		_engine = UnmanagedFacade::GetContainer()->CreateMGLEngine(_window);
		_canvas = gcnew Canvas(_engine);
	}

	void Window::SetEventHandler(IMngWindowEventHandler ^eh)
	{
		if (_evtHandler)
		{
			_window->DetachEventHandler(_evtHandler);
			delete _evtHandler;
		}
		_evtHandler = new WindowEventHandlerWrapper(eh);
		_window->AttachEventHandler(_evtHandler);
	}


}