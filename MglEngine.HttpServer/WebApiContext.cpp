#include "WebApiContext.h"

HttpResponse WebApiContext::HttpOk(std::string message)
{
	return HttpResponse::HttpOk(message, _context.request.version(), _context.request.keep_alive());
}

HttpResponse WebApiContext::HttpJson(std::string message)
{
	return HttpResponse::HttpJson(message, _context.request.version(), _context.request.keep_alive());
}
