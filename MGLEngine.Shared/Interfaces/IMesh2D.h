#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>

class IMesh2D   {
	
public:
	virtual uint32_t NVertices() = 0;
	virtual uint32_t NIndices() = 0;
	virtual void RenderMesh(MemoryStreamFloat2DAdapter positions,IndicesMemoryStream& indices) = 0;
	virtual void Draw(IDrawContext& context) = 0;

};