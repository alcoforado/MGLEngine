#include <MGLEngine.Shared/Resources/ImageLoader.h>
#include <stb_image.h>



StbiTexImage::~StbiTexImage() {
	if (data!=nullptr)
		stbi_image_free(data);
}

StbiTexImage::StbiTexImage() {

}


s_ptr<StbiTexImage> ImageLoader::LoadAsRGBA(std::string path)
{
	
	s_ptr<StbiTexImage> pImage = s_new<StbiTexImage>();
	int width, height,texChannels;
	stbi_uc* pixels = stbi_load(path.c_str(), &width, &height, &texChannels, STBI_rgb_alpha);

	pImage->texHeight = static_cast<unsigned>(height);
	pImage->texWidth = static_cast<unsigned>(width);
	pImage->texChannels = static_cast<unsigned>(texChannels);
	pImage->data = pixels;

	return pImage;
}
