#pragma 
#include "MGLEngine.Vulkan/Window/MWindow.h"



class VulkanTestsHelper
{
	static MGL::Window *pWindow;
public:
	static MGL::Window* GetWindow();
	VulkanTestsHelper();
	~VulkanTestsHelper();
};

