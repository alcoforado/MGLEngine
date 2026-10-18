#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <concepts>
#include <memory>
#include <string>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/TextureHandler.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Interfaces/AppConfiguration.h>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>
#include <MGLEngine.Shared/Resources/ResourceManager.h>


#include <typeindex>
#include <typeinfo>
#include <memory>

class MWindow;

class MGLEngine {
	protected:
		virtual bool IsShaderRegistered(const std::type_index shaderType);

	private:
		s_ptr<MWindow> _pWindow = nullptr;
		MGLEngine(const MGLEngine& eng);
		AppConfiguration _appConfig;
		std::map<std::type_index, size_t> _shadersIndex;
		std::vector<ShaderContext> _shaders;
		
		IGraphicLibrary& _gl;
		ResourceManager _resourceManager;
		
		std::map<std::string, GLID> _resourcesCache;

	private: //functions	

	public:
		MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig);
		~MGLEngine();


		template<std::default_initializable ShaderType>
		void AddShape(IDrawingObject& shape, const std::function<void(ShapeRegistrationConfig&)>& f) {
			std::type_index typeIndex(typeid(ShaderType));
			if (!this->IsShaderRegistered(typeIndex))
			{
				auto pShader = std::make_unique<ShaderType>();
				ShaderConfiguration options = {};
				pShader->Init(options);
				if (options.name.empty())
				{
					options.name = typeid(*pShader).name();
				}
				ShaderContext ctx(_shaders.size(),options);
				this->_shadersIndex[typeIndex] = _shaders.size();
				this->_shaders.push_back(ctx);
				
			}
			auto config = ShapeRegistrationConfig();
			f(config);
			auto& ctx = _shaders[_shadersIndex[typeIndex]];
			ctx.AddShape(&shape, config);

			
		};

		template<std::default_initializable ShaderType>
		void AddShape(IDrawingObject& shape) {
			this->AddShape<ShaderType>(shape, [](ShapeRegistrationConfig& c) {});
		};
		

		void LoadShaders();
		
		void Run();
		
};

