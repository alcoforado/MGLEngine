#pragma once
#include <string>
#include <memory>
#include <list>
#include <vulkan/vulkan.h>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
class IWindowEventHandler;
struct GLFWwindow;

namespace MGL {
	using std::string;
	
	
	

	


	class Window 
	{

		
		static void window_mouse_move_callback(GLFWwindow* window, double x, double y);
	private :
		GLFWwindow *_window;
		static bool isGLFWInitialized;
		bool _resizeOcurred;
		int _width;
		int _height;
		bool _isEasyRun;
		std::list<IWindowEventHandler*> _handlers;
	public:
		struct WindowSize {
			int32_t height;
			int32_t width;
		};

		void OnResize(int width, int heiight);
		Window(const WindowOptions& options);
		virtual ~Window();
		
		GLFWwindow* GLFWHandler() { return _window; }
		void Redraw();
		WindowSize Size(); 
		void AttachEventHandler(IWindowEventHandler *eh);
		void DetachEventHandler(IWindowEventHandler *eb);

	};

}