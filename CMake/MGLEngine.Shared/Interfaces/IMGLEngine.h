#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>
#include <concepts>
#include <memory>
#include <MGLEngine.Shared/Interfaces/IShader.h>
#include <typeindex>
#include <typeinfo>
class IMGLEngine {
	protected:
		virtual void RegisterShader(std::unique_ptr<IShader> pShader) =0;
		virtual bool IsShaderRegistered(const std::type_index shaderType) =0;
		virtual void AddShape(const std::type_index shaderTypeIndex, IDrawingObject& shape) =0;
	public:
		
		template<std::default_initializable ShapeType>
		void AddShape(IDrawingObject& shape) {
			std::type_index typeIndex(typeid(ShapeType));
			if (!this->IsShaderRegistered(typeIndex))
			{
				auto pShader = std::make_unique<ShapeType>();
				this->RegisterShader(std::move(pShader));
			}
			AddShape(typeIndex, shape);
		};

		virtual void Draw() = 0;
};