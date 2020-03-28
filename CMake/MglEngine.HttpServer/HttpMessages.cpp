#include "HttpMessages.h"

http::response<http::string_body> HttpResponses::Http500(std::string content,http::header<true> requests)
{
	auto res= http::response<http::string_body>();
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::content_type, "text/html");
    res.body() = "An error occurred: '" + std::string(content) + "'";
    res.prepare_payload();
    return res;

}
