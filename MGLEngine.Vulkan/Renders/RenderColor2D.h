#pragma once
#include "../RenderPipeline/VertexShaderByteCode.h"
#include "../RenderPipeline/FragmentShaderByteCode.h"
#include "../RenderPipeline/VulkanPipeline.h"
#include <memory>
#include <Utils/opointer.h>
class IRenderContext;

class RenderColor2D
{
	OPointer<VulkanPipeline> _pPipeline;
public:
	explicit RenderColor2D(IRenderContext& renderContext);
	~RenderColor2D();
	
};

