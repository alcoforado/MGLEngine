#include "Shape.h"
#include <MGLEngine.Shared/Utils/JsonParser/json.hpp>




Shape::Shape(int id, ITopology2D* top2d, IPainter2D* painter)
{
	Id = id;
	Top2d = top2d;
	Painter = painter;
	nlohmann::json json = new nlohmann::json();
}

Shape::~Shape()
{
}
