#pragma once
#include <MGLEngine.Shared/Window/IWindow.h>
#include <MGLEngine.Shared/Utils/opointer.h>
#include "MGLEngine.Vulkan/VulkanContext/VulkanInstance.h"
class IWindowEventHandler;
class VulkanContext;
struct GLFWwindow;

namespace MGL {
	class Window : public IWindow
	{
		static void window_mouse_move_callback(GLFWwindow* window, double x, double y);
	private :
		GLFWwindow *_window;
		OPointer<VulkanContext> _vkContext;
		static bool isGLFWInitialized;
		bool _resizeOcurred;
		int _width;
		int _height;
		bool _isEasyRun;
		std::list<IWindowEventHandler*> _handlers;
	public:
		void OnResize(int width, int heiight);
		Window();
		virtual ~Window();

		VulkanContext* GetVulkanContext() const { return _vkContext; }

		// Inherited via IWindow
		virtual void SetSize(int width, int height) override;
		virtual void EasyRun() override;
		virtual void PsychoRun() override;
		virtual void Redraw() override;
		virtual void AttachEventHandler(IWindowEventHandler *eh) override;
		virtual void DetachEventHandler(IWindowEventHandler *eb) override;
	};

}