#pragma once
#include <string>
#include <memory>
#include <list>
class IWindowEventHandler;
struct GLFWwindow;

namespace MGL {
	using std::string;
	
	class IWindowOptions {
	public:
		virtual void SetSize(int width, int height) = 0;
		virtual void SetFullScreen() = 0;
		virtual void SetTitle(string str) = 0;
	};

	class  WindowOptions: IWindowOptions {
	public:
		int Height; 
		int Width;
		bool FullScreen;
		string Title;
	public: 
		virtual void SetSize(int width, int height) { Height = height; Width = width; }
		virtual void SetFullScreen() { FullScreen = true; }
		virtual void SetTitle(string str) { Title = str; }
	};

	


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


		
		void Redraw();
		void AttachEventHandler(IWindowEventHandler *eh);
		void DetachEventHandler(IWindowEventHandler *eb);

	};

}