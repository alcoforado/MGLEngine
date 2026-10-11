
#pragma once
#include <string>
#include <filesystem>
#include <MGLEngine.Shared/utils.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>

class StbiTexImage : public ITexImage {
public:
	StbiTexImage();
	~StbiTexImage();
};

class ImageLoader {

	
private:
public:
	ImageLoader();
	s_ptr<StbiTexImage> LoadAsRGBA(std::string path);
	
	

};
