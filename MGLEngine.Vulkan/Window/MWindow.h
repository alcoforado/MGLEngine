#pragma once
#include <Window/IWindow.h>
class VulkanContext;
struct GLFWwindow;

namespace MGL {
	class Window : public IWindow
	{
	private :
		GLFWwindow *_window;
		VulkanContext *_vkContext;
		static bool isGLFWInitialized;
		int _width;
		int _height;
	public:
		Window();
		virtual ~Window();

		VulkanContext* GetVulkanContext() const { return _vkContext; }

		// Inherited via IWindow
		virtual void SetSize(int width, int height) override;
		virtual void EasyRun() override;
		virtual void PsychoRun() override;
	};

}