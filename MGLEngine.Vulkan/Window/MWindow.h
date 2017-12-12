#pragma once
#include <MGLEngine.Shared/Window/IWindow.h>
#include <MGLEngine.Shared/Utils/opointer.h>
#include "MGLEngine.Vulkan/VulkanContext/VulkanInstance.h"
class VulkanContext;
struct GLFWwindow;

namespace MGL {
	class Window : public IWindow
	{
	private :
		GLFWwindow *_window;
		OPointer<VulkanContext> _vkContext;
		static bool isGLFWInitialized;
		bool _resizeOcurred;
		int _width;
		int _height;
		bool _isEasyRun;
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
	};

}