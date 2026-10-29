#pragma once
#include <cstddef>

#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Interfaces/ITexImage.h>
#include <MGLEngine.Shared/Interfaces/GLID.h>
#include <MGLEngine.Shared/Container/MGLContainer.h>
#include <vector>


class GlobalBindingsTable;



class IGraphicLibrary {
	public:
		virtual GLID LoadTexture(ITexImage& img) = 0;
		virtual void LoadShaders(std::vector<ShaderContext>& shaders, MGLContainer& container) = 0;
		virtual void Run(std::vector<ShaderContext>& shaders, MGLContainer& container)=0;
		virtual GLID CreateUbo(uint32_t binding, size_t sizeOfDataType)=0;
		virtual ~IGraphicLibrary() {}
};

