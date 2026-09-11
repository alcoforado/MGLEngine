#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <concepts>
#include <memory>
#include <string>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/TextureHandler.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Interfaces/IAppConfiguration.h>
#include <MGLEngine.Shared/Interfaces/IWindowOptions.h>


#include <typeindex>
#include <typeinfo>
#include <memory>

class IMGLEngine {

	protected:
		virtual bool IsShaderRegistered(const std::type_index shaderType);

	private:
		IMGLEngine(const IMGLEngine& eng);
		
		std::map<std::type_index, size_t> _shadersIndex;
		std::vector<ShaderContext> _shaders;
		s_ptr<GlobalBindingsTable> _pGlobalBindingsTable = s_new<GlobalBindingsTable>();
		
		
		IGraphicLibrary& _gl;
	public:
		IMGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig);
		~IMGLEngine();


		template<std::default_initializable ShaderType>
		void AddShape(IDrawingObject& shape, const std::function<void(IShapeRegistrationConfig&)>& f) {
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
			this->AddShape<ShaderType>(shape, [](IShapeRegistrationConfig& c) {});
		};

		void SetGlobalBindingTable();
		
		void Run();
		
};

