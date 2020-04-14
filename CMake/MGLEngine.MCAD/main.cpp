#include <MglEngine.HttpServer\HttpServer.h>
#include <MGLEngine.Vulkan/Window/MWindow.h>
#include <MGLEngine.Shared\ShapesService\ShapesService.h>
#include "ShapesController.h"
#include <thread>
class HelloWorldC {
public:
    HttpResponse HelloWorld(WebApiContext& cntx)
    {
        return cntx.HttpOk("Hello World");
    }
};


void RunServer(MGL::Window *pWindow)
{

    HttpServer server(8765);

   s_ptr<HelloWorldC> hello = std::make_shared<HelloWorldC>();
   server.MapRoute("GET", "hello", hello, &HelloWorldC::HelloWorld);
        
        //Create and Register ShapesController
    s_ptr<ShapesService> shService = std::make_shared<ShapesService>(pWindow);
    s_ptr<ShapesController> shapesC = std::make_shared<ShapesController>(shService);

    server.MapRoute("GET", "api/shapemngr/shapetypes", shapesC, &ShapesController::GetShapeTypes);
    server.MapRoute("GET", "api/shapemngr/rendertypes", shapesC, &ShapesController::GetRenderTypes);




    server.run();
}


int main()
{
    
    MGL::Window window;
   window.SetSize(800, 800);
   std::thread(RunServer,&window).detach();
  
   window.EasyRun();

    return -1;
}