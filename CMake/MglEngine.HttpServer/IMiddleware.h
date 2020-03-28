#include "boost_deps.h"
#include "HttpContext.h"
#pragma once

namespace http = boost::beast::http;




class IMiddleware
{
	virtual void Process(HttpContext* cntx) = 0;

};
