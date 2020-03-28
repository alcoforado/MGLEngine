#pragma once
#include "IMiddleware.h"
#include "Router.h"
class RouterEntry {


};






#pragma once
class WebApiMiddletier : public IMiddleware
{
	
private:
	Router RouteTable;
public:
	virtual void Process(HttpContext& cntx);

};
