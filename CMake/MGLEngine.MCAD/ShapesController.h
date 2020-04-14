#pragma once
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/ShapesService/ShapesService.h>
#include <MglEngine.HttpServer\IController.h>
#include <MglEngine.HttpServer\WebApiContext.h>

class ShapesController 
{
private:
	s_ptr<ShapesService> _pService;
public:
	ShapesController(s_ptr<ShapesService> pService):_pService(pService){}

	HttpResponse GetRenderTypes(WebApiContext &context);

	HttpResponse GetShapeTypes(WebApiContext &context);




};
