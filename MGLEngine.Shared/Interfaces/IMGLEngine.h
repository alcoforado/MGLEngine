#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <concepts>
#include <memory>
#include <string>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/TextureHandler.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>

#include <typeindex>
#include <typeinfo>
#include <memory>

class IMGLEngine {

	protected:
		virtual bool IsShaderRegistered(const std::type_index shaderType);

	private:
		std::map<std::type_index, ShaderContext> _shaders;
		s_ptr<GlobalBindingsTable> _pGlobalBindingsTable = s_new<GlobalBindingsTable>();
		
	public:
		
		template<std::default_initializable ShapeType>
		void AddShape(IDrawingObject& shape, const std::function<void(IShapeRegistrationConfig&)>& f) {
			std::type_index typeIndex(typeid(ShapeType));
			if (!this->IsShaderRegistered(typeIndex))
			{
				auto pShader = std::make_unique<ShapeType>();
				ShaderConfiguration options = {};
				pShader->Init(options);
				if (options.name.empty())
				{
					options.name = typeid(*pShader).name();
				}
				ShaderContext ctx(options, _pGlobalBindingsTable);
				this->_shaders[typeIndex] = ctx;
			}
			auto config = ShapeRegistrationConfig();
			f(config);
			auto& ctx = _shaders[typeIndex];
			ctx.AddShape(&shape, config);

			
		};

		template<std::default_initializable ShapeType>
		void AddShape(IDrawingObject& shape) {
			this->AddShape(shape, [](IShapeRegistrationConfig& c) {});
		};

		void SetGlobalBindingTable();
		
		virtual void Run() = 0;
};

