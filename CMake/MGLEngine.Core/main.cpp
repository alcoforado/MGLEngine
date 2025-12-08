#include <exception>
#include <iostream>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Shared/MGLContainer.h>

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