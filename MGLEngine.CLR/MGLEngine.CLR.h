// MGLEngine.CLR.h
#include <Window/IWindow.h>
#include "UnmanagedFacade.h"
#include "Canvas.h"
#pragma once

using namespace System;

namespace MGLEngineCLR {

	public ref class Window
	{
		Canvas^ _canvas;
		IWindow *_window;
	public:
		Window()
		{
			_window = UnmanagedFacade::GetContainer()->CreateWindow();
			_canvas = gcnew Canvas();
		}

		Canvas^ GetCanvas() { return _canvas; }

		void SetSize(int width, int height)
		{
			_window->SetSize(width, height);
		}
		void EasyRun()
		{
			_window->EasyRun();
		}
		void PsychoRun()
		{
			_window->PsychoRun();
		}

		~Window()
		{
			delete _window;
		}
	};
}
