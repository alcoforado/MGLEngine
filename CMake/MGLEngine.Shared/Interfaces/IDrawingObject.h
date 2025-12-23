#include <cstdint>
#include <MGLEngine.Shared/Interfaces/IRenderDataContext.h>
#include <MGLEngine.Shared/Interfaces/IDrawContext.h>
#pragma once
class IDrawingObject
{
	public:
		virtual uint32_t NVertices() = 0;
		virtual uint32_t NIndices() = 0;
		virtual void RenderData(IRenderDataContext &context ) = 0;
		virtual void Draw(IDrawContext& context) = 0;
		virtual const std::type_info& ShaderType() = 0;
};

