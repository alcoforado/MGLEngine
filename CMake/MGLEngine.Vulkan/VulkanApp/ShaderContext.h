#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>


class ShaderContext {
public:
	ShaderConfiguration options;
	VkPipeline pipeline;
	std::vector<IDrawingObject*> objects;
	VulkanBuffer vBuffer;

	BindingManager Binding;

	ShaderContext() {
		pipeline = VK_NULL_HANDLE;
	}

};


