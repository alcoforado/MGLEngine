#include "boost_deps.h"
class HttpServer
{
private:
	boost::asio::io_context _ioc;
	asio::ip::tcp::endpoint _host;

	void process_request(asio::ip::tcp::socket& socket);



public:
	HttpServer(int port);



	void run();


};
