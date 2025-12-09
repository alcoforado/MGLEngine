#include "ShaderConfiguration.h"
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>



class ShaderContext {
public:
	IShader& shader;
	ShaderConfiguration options;
	VkPipeline pipeline;
	std::vector<IDrawingObject*> objects;
	VulkanBuffer vBuffer;

	uint32_t GetVerticesDataSize() const {
		uint32_t nVertices = 0;
		for (auto &elem:objects) {
			nVertices += elem->NVertices();
		}
		return nVertices * options.GetTotalAttributesSize();
	}


};


