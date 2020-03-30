#include "HttpServer.h"


class HelloWorldC {
    public:
        HttpResponse HelloWorld(WebApiContext& cntx)
        {
            return cntx.HttpOk("Hello World");
        }
};

int main() {
    s_ptr<HelloWorldC> hello = std::make_shared<HelloWorldC>();
    HttpServer server(8765);
    server.MapRoute("GET", "hello", hello, &HelloWorldC::HelloWorld);
        server.run();
}