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

	std::vector<s_ptr<FontAtlas>> fontsMetadata;
	std::filesystem::path _base_path;

	std::string GetFullPath(std::string relPath);
	IGraphicLibrary &_gl;
public:


	ResourceManager(IGraphicLibrary &gl,std::string basePath = "");
	Resource Load(ResourceRef &imgRef);

};