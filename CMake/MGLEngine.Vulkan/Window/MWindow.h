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
		void OnResize(int width, int heiight);
		Window(const WindowOptions& options);
		virtual ~Window();
		int Height(){ return _height; }
		int Width() { return _width; }
		GLFWwindow* GLFWHandler() { return _window; }
		void Redraw();
		void AttachEventHandler(IWindowEventHandler *eh);
		void DetachEventHandler(IWindowEventHandler *eb);

	};

}