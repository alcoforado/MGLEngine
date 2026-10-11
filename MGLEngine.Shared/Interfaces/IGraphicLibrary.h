#pragma once
#include <cstddef>
#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <vector>

struct ITexImage {
	void* data;
	int texWidth;
	int texHeight;
	int texChannels;
};


class IGraphicLibrary {
	public:
		virtual GLID LoadTexture(ITexImage& img) = 0;
		virtual void LoadShaders(std::vector<ShaderContext>& shaders, GlobalBindingsTable& globalBindingTbl) = 0;
		virtual void Run(std::vector<ShaderContext>& shaders,GlobalBindingsTable& bindingTable)=0;
};

