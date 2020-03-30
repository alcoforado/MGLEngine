#include "VulkanTestsHelper.h"

MGL::Window *VulkanTestsHelper::pWindow = nullptr;

MGL::Window* VulkanTestsHelper::GetWindow()
{
	if (!pWindow)
		pWindow = new MGL::Window();
	return pWindow;
}


VulkanTestsHelper::VulkanTestsHelper()
{
}


VulkanTestsHelper::~VulkanTestsHelper()
{
}
