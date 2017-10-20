// MGLEngine.CLR.h
#include <Window/IWindow.h>
#include "UnmanagedFacade.h"
#pragma once

using namespace System;

class IMGLEngine;

namespace MGLEngineCLR {
	ref class Canvas;
	

	public ref class Window
	{
		Canvas^ _canvas;
		IMGLEngine *_engine;
		IWindow *_window;

	public:
		Window();
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
