#pragma once

#include "boost_deps.h"
class HttpResponses
{
public:
	http::response<http::string_body> Http500(std::string content);
};
