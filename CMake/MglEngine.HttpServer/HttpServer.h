#include "boost_deps.h"
#include "IMiddleware.h"
#include "WebApiMiddletier.h"


class HttpServer
{
private:
	boost::asio::io_context _ioc;
	asio::ip::tcp::endpoint _host;

	void process_request(asio::ip::tcp::socket& socket);

	std::list<std::shared_ptr<IMiddleware>> _middlewares;
	std::shared_ptr<WebApiMiddleware> _webapi;
	HttpServer& AddWebApi();

public:
	HttpServer(int port);
	
	template<class Controller>
	void MapRoute(std::string method, std::string path, s_ptr<Controller> cntrl, HttpResponse (Controller::* f)(WebApiContext&)) {
		using std::placeholders::_1;
		auto call = std::bind(f, cntrl,_1);
		_webapi->RouteTable.Map(Router::parseHttpMethod(method), path, call);
		
	}
	
		
	void run();


};
