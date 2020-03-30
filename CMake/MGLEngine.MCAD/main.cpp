#include <MglEngine.HttpServer\HttpServer.h>
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include <thread>
class HelloWorldC {
public:
    HttpResponse HelloWorld(WebApiContext& cntx)
    {
        return cntx.HttpOk("Hello World");
    }
};



void RunServer()
{

        s_ptr<HelloWorldC> hello = std::make_shared<HelloWorldC>();
        HttpServer server(8765);
        server.MapRoute("GET", "hello", hello, &HelloWorldC::HelloWorld);
        server.run();
}


int main()
{
    
    //std::thread(RunServer).join();
    MGL::Window window;
   // window.SetSize(800, 800);
   window.EasyRun();

    return -1;
}