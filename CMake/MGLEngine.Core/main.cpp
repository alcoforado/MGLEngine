#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/MGLContainer.h>
#include <MGLEngine.Shared/Mesh/OrthoRect2D.h>
#include <MGLEngine.Shared/Shaders/Color2D/ShaderColor2D.h>
int main()
{
	MGLContainer container;
	auto pApp = container.GetApp();
	IApp &app = *pApp;

	app.WindowConfig([](IWindowOptions &options) {
		options.SetSize(800,800);
		options.SetTitle("MGLEngine Test App");
	});
	app.AppConfig([](IAppConfiguration &config) {
		config.EnableDebugLayer(true);
		config.EnableVSync(true);
		config.AddShader("ShaderColor2D",new ShaderColor2D())
	});



	try {
		eassert(1 == 2, "Test eassert exception");
	}
	catch (const std::exception& e) 
	{
		std::cout << "Exception caught " << e.what() << std::endl;
	}
	return 1;
}