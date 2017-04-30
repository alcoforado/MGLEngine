#pragma once
#include <Window/IWindow.h>

namespace MGL {
	class Window : public IWindow
	{

	private :
		static bool isGLFWInitialized;
		int _width;
		int _height;
	public:
		Window();
		virtual ~Window();

		// Inherited via IWindow
		virtual void SetSize(int width, int height) override;
		virtual void EasyRun() override;
	};

}