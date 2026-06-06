#include "ResourceManager.h"
#include <stb_image.h>
#include <gli/gli.hpp>
ImgHandler ResourceManager::LoadImage(ImageConfig config)
{
	ImageResource res;

	res.name = config.filePath;

	gli::texture Texture = gli::load(config.filePath);

	auto id = this->_images.size();
	this->_images.push_back(res);

	return ImgHandler(id);

}