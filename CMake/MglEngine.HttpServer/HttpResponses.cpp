#include "HttpResponses.h"

http::response<http::string_body> HttpResponses::Http500(std::string content,int version, bool keep_alive)
{
	auto res= http::response<http::string_body>(http::status::internal_server_error, version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(keep_alive);
    res.set(http::field::content_type, "text/html");
    res.body() = "An error occurred: '" + std::string(content) + "'";
    res.prepare_payload();
    return res;

}
