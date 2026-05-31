#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <concepts>
#include <memory>
#include <string>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <MGLEngine.Shared/Interfaces/TextureHandler.h>
#include <MGLEngine.Shared/Interfaces/ShapeRegistrationConfig.h>
#include <MGLEngine.Shared/Utils/ovector.h>
#include <typeindex>
#include <typeinfo>
#include <memory>

class IMGLEngine {

	protected:
		virtual void RegisterShader(std::unique_ptr<IShader> pShader) =0;
		virtual bool IsShaderRegistered(const std::type_index shaderType) =0;
		virtual void AddShape(const std::type_index shaderTypeIndex, IDrawingObject& shape,ShapeRegistrationConfig& config) =0;
		
	public:
		
		template<std::default_initializable ShapeType>
		void AddShape(IDrawingObject& shape, std::function<void(ShapeRegistrationConfig&)>& f) {
			std::type_index typeIndex(typeid(ShapeType));
			if (!this->IsShaderRegistered(typeIndex))
			{
				auto pShader = std::make_unique<ShapeType>();
				this->RegisterShader(std::move(pShader));
			}
			auto config = ShapeRegistrationConfig();
			f(config);
			AddShape(typeIndex, shape, config);
		};

		template<std::default_initializable ShapeType>
		void AddShape(IDrawingObject& shape) {
			std::type_index typeIndex(typeid(ShapeType));
			if (!this->IsShaderRegistered(typeIndex))
			{
				auto pShader = std::make_unique<ShapeType>();
				this->RegisterShader(std::move(pShader));
			}
			auto config = ShapeRegistrationConfig();
			AddShape(typeIndex, shape, config);
		};

		virtual TextureHandler  RegisterTexture(std::string path) = 0;
		
		virtual void Run() = 0;
};

