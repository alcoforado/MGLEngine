#pragma once

#include "boost_deps.h"
class HttpResponse : public http::response<http::string_body>
{
public:
	HttpResponse(http::status status, unsigned int version)
	:http::response<http::string_body>(status,version)
	{}
	
	HttpResponse() {}
	
	static HttpResponse Http500(std::string content, int version, bool keep_alive);
	static HttpResponse Http404(std::string content,  int version, bool keep_alive);
	static HttpResponse HttpOk(std::string content, int version, bool keep_alive);
	static HttpResponse HttpJson(std::string content, int version, bool keep_alive);


};
