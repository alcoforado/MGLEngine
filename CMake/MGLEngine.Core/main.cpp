#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/MGLContainer.h>
#include <MGLEngine.Shared/Mesh/OrthoRect2D.h>
#include <MGLEngine.Shared/Shaders/Color2D/VertexColor2D.h>

int main()
{
	
	MGLContainer container;
	auto pApp = container.GetApp();
	IAppBuilder &app = *pApp;

	app.WindowConfig([](IWindowOptions &options) {
		options.SetSize(800,800);
		options.SetTitle("MGLEngine Test App");
	});
	app.AppConfig([](IAppConfiguration &config) {
		config.EnableDebugLayer(true);
		config.EnableVSync(true);
	//	config.AddShader<ShaderColor2D>();
	});

	IMGLEngine &engine=app.Init();
	
	auto rect = OrthoRect2D(glm::vec2(0.0f, 0.0f), 1.0f, 1.0f);
	auto rectDraw = VertexColor2D(engine, rect, { glm::vec4(1,0,0,1),glm::vec4(0,0,1,1) });

}

