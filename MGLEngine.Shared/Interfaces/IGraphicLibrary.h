#pragma once
#include <cstddef>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <MGLEngine.Shared/Resources/ImageLoader.h>
#include <vector>
class IGraphicLibrary {
	public:
		virtual GLID LoadTexture(TexImage& img) = 0;
		virtual void LoadShaders(std::vector<ShaderContext>& shaders, GlobalBindingsTable& globalBindingTbl) = 0;
		virtual void Run(std::vector<ShaderContext>& shaders,GlobalBindingsTable& bindingTable)=0;
};