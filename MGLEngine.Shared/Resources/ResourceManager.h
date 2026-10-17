#pragma once

#include <filesystem>
#include <MGLEngine.Shared/utils.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared/Resources/ImageLoader.h>
#include "FreeTypeLoader.h"










struct Resource {
	GLID glid;
	size_t MetadataId;

};

class ResourceManager {

	ImageLoader _imgLoader;
	FreeTypeLoader _freeTypeLoader;
	s_ptr<GlobalBindingsTable> _pGlobalBindingsTable = s_new<GlobalBindingsTable>();
	std::vector<s_ptr<const FontAtlas>> vFontAtlas;
	std::filesystem::path _base_path;

	std::string GetFullPath(std::string relPath);
	IGraphicLibrary &_gl;
public:


	ResourceManager(IGraphicLibrary &gl,std::string basePath = "");
	Resource Load(ResourceRef &imgRef);
	void RegisterShaderBindings(ShaderContext& shader);
	void RegisterShapeResources(ShaderContext& shader);
	void LoadAllResources();
	


	s_ptr<GlobalBindingsTable> GetGlobalBindingsTable(){ return _pGlobalBindingsTable; }
	const FontAtlasMetadata& GetFontMetadata(std::string sampleName) const;

};