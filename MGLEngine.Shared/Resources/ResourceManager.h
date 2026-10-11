#pragma once

#include <filesystem>
#include <MGLEngine.Shared/utils.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared/Resources/ImageLoader.h>










struct Resource {
	GLID glid;
	unsigned int MetadataId;

};

class ResourceManager {

	ImageLoader _imgLoader;

	std::filesystem::path _base_path;

	std::string GetFullPath(std::string relPath);
	IGraphicLibrary &_gl;
public:


	ResourceManager(IGraphicLibrary &gl,std::string basePath = "");
	Resource Load(ImageRef &imgRef);

};