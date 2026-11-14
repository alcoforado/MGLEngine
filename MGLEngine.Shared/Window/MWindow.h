#pragma once
#include <string>
#include <memory>
#include <list>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Events/KeyboardSource.h>
class IWindowEventHandler;
struct GLFWwindow;

	using std::string;
	
	
	

	


	class MWindow 
	{

		
		static void window_mouse_move_callback(GLFWwindow* window, double x, double y);
		static void window_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void window_keyboard_callback(GLFWwindow* window, double x, double y);

	private :
		GLFWwindow *_window;
		static bool isGLFWInitialized;
		bool _resizeOcurred;
		int _width;
		int _height;
		bool _isEasyRun;
		std::list<IWindowEventHandler*> _handlers;
		KeyboardSource _keyboard;
	public:
		struct WindowSize {
			int32_t height;
			int32_t width;
		};

		void OnResize(int width, int heiight);
		MWindow(const WindowOptions& options);
		virtual ~MWindow();
		
		GLFWwindow* GLFWHandler() { return _window; }
		void Redraw();
		WindowSize Size(); 

		void AttachEventHandler(IWindowEventHandler *eh);
		void DetachEventHandler(IWindowEventHandler *eb);
		bool ShouldClose();
		void PollEvents();
		IObservable<KeyboardEvent>& OnKeyPress() { return _keyboard; }
	};

