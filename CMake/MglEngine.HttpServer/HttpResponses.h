#pragma once

#include "boost_deps.h"
class HttpResponses
{
public:
	static http::response<http::string_body> Http500(std::string content,  int version, bool keep_alive);
};
