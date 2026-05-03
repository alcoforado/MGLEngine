#include "boost_deps.h"
#include "HttpContext.h"
#pragma once

namespace http = boost::beast::http;




class IMiddleware
{
public:
	virtual void process(HttpContext& cntx) = 0;

};
