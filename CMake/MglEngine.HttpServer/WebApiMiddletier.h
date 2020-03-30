#pragma once
#include "IMiddleware.h"
#include "Router.h"







#pragma once
class WebApiMiddleware : public IMiddleware
{
	
public:
	Router RouteTable;
public:
	virtual void process(HttpContext& cntx) override;
	

};
