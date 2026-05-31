#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/MGLContainer.h>
#include <MGLEngine.Shared/Mesh/OrthoRect2D.h>
#include <MGLEngine.Shared/Shaders/Color2D/VertexColor2D.h>
#include <MGLEngine.Shared/Shaders/Texture2D/Sprite2D.h>

#include <MGLEngine.Shared/Utils/Exception.h>


void Example1(IMGLEngine& engine)
{
	auto rect = OrthoRect2D(glm::vec2(-1.0f, -0.5f), 0.5f, 0.5f);
	auto rect2 = OrthoRect2D(glm::vec2(0.0f, -0.5f), 0.5f, 0.5f);
	auto rectDraw = VertexColor2D(engine, rect, { glm::vec4(1,0,0,1),glm::vec4(0,1,0,1),glm::vec4(0,1,0,1) });
	auto rectDraw2 = VertexColor2D(engine, rect2, { glm::vec4(1,1,0,1),glm::vec4(1,1,0,1),glm::vec4(1,0,1,1),glm::vec4(1,0,0,1) });
	engine.Run();
}

void Example2(IMGLEngine& engine)
{
	auto sprite = Sprite2D(engine, glm::vec2(-1.0f, -0.5f), 0.5f, 0.5f, "./pic");
}

int main()
{
	try {
		MGLContainer container;
		auto pApp = container.GetApp();
		IAppBuilder& app = *pApp;

		app.WindowConfig([](IWindowOptions& options) {
			options.SetSize(800, 800);
			options.SetTitle("MGLEngine Test App");
			});
		app.AppConfig([](IAppConfiguration& config) {
			config.EnableDebugLayer(true);
			config.EnableVSync(true);
			config.SetDoubleBuffer();
			config.SetVersion(1, 2, 0);
			});

		IMGLEngine& engine = app.Init();

		Example2(engine);
		
		
	}
	catch (std::exception e)
	{
		std::cout << "Error: " << e.what();
	}
	catch (Exception e)
	{
		std::cout << "Fatal Error:  " << e.getError();
	}
}

