#include "ImageLoader.h"
#include <stb_image.h>

ImageLoader::ImageLoader(std::string basePath)
	:_base_path(basePath)
{

}

s_ptr<TexImage> ImageLoader::LoadAsRGBA(std::string relPath)
{
	std::string path = GetFullPath(relPath);
	s_ptr<TexImage> pImage = s_new<TexImage>();
	stbi_uc* pixels = stbi_load(path.c_str(), &(pImage->texWidth), &(pImage->texHeight), &(pImage->texChannels), STBI_rgb_alpha);
	pImage->data = pixels;

	return pImage;
}

std::string ImageLoader::GetFullPath(std::string relPath)
{
	if (_base_path.empty())
		return relPath;
	else
		return (_base_path / std::filesystem::path(relPath)).string();
}