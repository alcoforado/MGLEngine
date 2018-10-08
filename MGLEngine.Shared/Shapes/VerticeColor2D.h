#pragma once

#include <MGLEngine.Shared/Interfaces/IShape2D.h>
#include "MGLEngine.Shared/Interfaces/IPainter.h"
#include "MGLEngine.Shared/VerticeData/Color2D.h"

class VerticeColor2D : public IShape2D, public IPainter<Color2D>
{
public:
	std::vector<glm::vec3> Colors;

	std::string Serialize() override;
	void Deserialize(std::string str) override;
	IShapeHandle* Draw(ICanvas* canvas, ITopology2D* top) override;
	void Write(IArray<Color2D>& array) override;
};
