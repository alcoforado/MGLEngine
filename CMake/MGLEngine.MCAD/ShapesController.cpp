#include "ShapesController.h"
#include <MglEngine.HttpServer\HttpServer.h>
#include <MGLEngine.Shared\Utils\JsonParser\mjson.h>
HttpResponse ShapesController::GetShapeTypes(WebApiContext& context)
{
	auto &m=this->_pService->GetShapes2D();
	json v;
	for (auto p : m)
	{
		json o;
		o["Dim"] = 2;
		o["Name"] = p.first;
		
		v.push_back(o);
	}
	
	auto result = v.dump();
	return context.HttpJson(result);
	
}

HttpResponse ShapesController::ReserveId(WebApiContext& context)
{
	
	std::string shapeType = context.getRouteParameters()["shapeType"];
	std::string r=_pService->ReserveShapeId(shapeType);
	json v = r;
	return context.HttpJson(v.dump());
}


HttpResponse ShapesController::GetRenderTypes(WebApiContext& context)
{
	auto& m = this->_pService->GetPainters2D();
	json v;
	for (auto p : m)
	{
		json o;
		o["Dim"] = 2;
		o["Name"] = p.first;

		v.push_back(o);
	}

	auto result = v.dump();
	return context.HttpJson(result);

}