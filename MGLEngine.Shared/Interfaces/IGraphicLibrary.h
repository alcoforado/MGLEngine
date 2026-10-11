#pragma once
#include <cstddef>

enum ImageFormat {
	R8G8B8A8 =0,
	R8 = 1
};

struct ITexImage {
	void* data;
	unsigned int texWidth;
	unsigned int texHeight;
	unsigned int texChannels;
	ImageFormat format;
};

#include <MGLEngine.Shared/Shaders/ShaderContext.h>
#include <MGLEngine.Shared/Shaders/GlobalBindingsTable.h>
#include <vector>



class IGraphicLibrary {
	public:
		virtual GLID LoadTexture(ITexImage& img) = 0;
		virtual void LoadShaders(std::vector<ShaderContext>& shaders, GlobalBindingsTable& globalBindingTbl) = 0;
		virtual void Run(std::vector<ShaderContext>& shaders,GlobalBindingsTable& bindingTable)=0;
};

