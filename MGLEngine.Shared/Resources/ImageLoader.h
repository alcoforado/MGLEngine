
#pragma once
#include <string>
#include <filesystem>
#include <MGLEngine.Shared/utils.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>

class TexImage : public ITexImage {
public:
	TexImage();
	~TexImage();
};

class ImageLoader {

	
private:
public:
	ImageLoader();
	s_ptr<TexImage> LoadAsRGBA(std::string path);
	
	

};
