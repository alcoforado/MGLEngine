#pragma once

/**
 * Internal Interface that every VulkanShader should implement
 */

class IDrawContext;
class IVulkanShader
{
public:
	virtual void Draw(IDrawContext *pDrawContext) = 0;
};