#pragma once

#include <MGLEngine.Shared/Interfaces/IPainter2D.h>
#include "MGLEngine.Shared/Interfaces/IShaderDataWriter.h"
#include "MGLEngine.Shared/VerticeData/Color2D.h"
#include "MGLEngine.Shared/Painters/CyclicColor.h"

class VerticeColor2D : public IPainter2D, public CyclicColor<Color2D>
{
public:
	

	IShapeHandle* RegisterInShader(ICanvas* canvas, ITopology2D* top) override;
	virtual std::string Serialize() override;
	virtual void Deserialize(std::string str) override;

	virtual ~VerticeColor2D(){}
};
