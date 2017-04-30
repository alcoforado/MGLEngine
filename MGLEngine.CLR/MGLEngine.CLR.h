// MGLEngine.CLR.h
#include <Window/IWindow.h>
#include "UnmanagedFacade.h"
#pragma once

using namespace System;

namespace MGLEngineCLR {

	public ref class Window
	{
		IWindow *_window;
	public:
		Window()
		{
			_window = UnmanagedFacade::GetContainer()->CreateWindow();

		}
		void SetSize(int width, int height)
		{
			_window->SetSize(width, height);
		}
		void EasyRun()
		{
			_window->EasyRun();
		}


		~Window()
		{
			delete _window;
		}
	};
}
