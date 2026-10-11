#include <MGLEngine.Shared/Resources/ImageLoader.h>
#include <stb_image.h>



TexImage::~TexImage() {
	if (data!=nullptr)
		stbi_image_free(data);
}

TexImage::TexImage() {

}


s_ptr<TexImage> ImageLoader::LoadAsRGBA(std::string path)
{
	
	s_ptr<TexImage> pImage = s_new<TexImage>();
	stbi_uc* pixels = stbi_load(path.c_str(), &(pImage->texWidth), &(pImage->texHeight), &(pImage->texChannels), STBI_rgb_alpha);
	
	
	pImage->data = pixels;

	return pImage;
}
