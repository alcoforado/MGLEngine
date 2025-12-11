#pragma once
#include <MGLEngine.Shared\Interfaces\IAppBuilder.h>
#include <memory>

	class MGLContainer
	{
	public:

		
		std::shared_ptr<IAppBuilder> GetApp();

	};

