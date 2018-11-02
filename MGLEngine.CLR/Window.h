// MGLEngine.CLR.h
#include <Window/IWindow.h>
#include "UnmanagedFacade.h"
#pragma once



class IMGLEngine;

namespace MGLEngineCLR {
	ref class Canvas;


	enum MouseButton { BUTTON_RIGHT, BUTTON_LEFT };

	public ref struct MngClickEvent
	{
		public:
			bool IsPressed;
			bool IsReleased;
			MouseButton MouseButton;
	};

	public interface class IMngWindowEventHandler
	{
		public:
			void OnMouseMove(double x, double y);
			void OnMouseClick(MngClickEvent^ evt);
	};


	

	public ref class Window
	{
		Canvas^ _canvas;
		IMGLEngine *_engine;
		IWindow *_window;
		IWindowEventHandler *_evtHandler = nullptr;
	public:
		Window();
		Canvas^ GetCanvas() { return _canvas; }

		IWindow* GetNativeHandle() { return _window; }
		
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
		
		void SetEventHandler(IMngWindowEventHandler ^eh);

		~Window()
		{
			delete _window;		
		}
	};

}
