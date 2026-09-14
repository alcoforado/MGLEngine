#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/Mesh/OrthoRect2D.h>
#include <MGLEngine.Shared/Shaders/Color2D/VertexColor2D.h>
#include <MGLEngine.Shared/Shaders/Texture2D/Sprite2D.h>

#include <MGLEngine.Shared/Utils/Exception.h>
#include <MGLEngine.Shared/AppBuilder.h>


void Example1(MGLEngine& engine)
{
	auto rect = OrthoRect2D(glm::vec2(-1.0f, -0.5f), 0.5f, 0.5f);
	auto rect2 = OrthoRect2D(glm::vec2(0.0f, -0.5f), 0.5f, 0.5f);
	auto rectDraw = VertexColor2D(engine, rect, { glm::vec4(1,0,0,1),glm::vec4(0,1,0,1),glm::vec4(0,1,0,1) });
	auto rectDraw2 = VertexColor2D(engine, rect2, { glm::vec4(1,1,0,1),glm::vec4(1,1,0,1),glm::vec4(1,0,1,1),glm::vec4(1,0,0,1) });
	engine.Run();
}

void Example2(MGLEngine& engine)
{
	auto sprite = Sprite2D(engine, glm::vec2(-1.0f, -0.5f), 0.5f, 0.5f, "./pic");
}

int main()
{
	try {
		AppBuilder app;

		app.WindowConfig([](IWindowOptions& options) {
			options.SetSize(800, 800);
			options.SetTitle("MGLEngine Test App");
			});
		app.AppConfig([](AppConfiguration& config) {
			config.EnableDebugLayer(true);
			config.EnableVSync(true);
			config.SetDoubleBuffer();
			config.SetVersion(1, 2, 0);
			});

		MGLEngine& engine = app.Init();

		Example1(engine);
		
		
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

