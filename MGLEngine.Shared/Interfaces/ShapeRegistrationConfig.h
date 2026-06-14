#pragma once
#include <string>
#include <list>

class ImageConfig {
	friend class ShapeRegistrationConfig;
public:
	std::string filePath;
	std::string samplerName;
	~ImageConfig() {

	}
};

class ShapeRegistrationConfig
{
	
	std::list<ImageConfig> _imgs;

public:
	ShapeRegistrationConfig()
	{
	}


	ImageConfig& BindImage(std::string path,std::string samplerName)
	{
		ImageConfig im;
		im.filePath = path;
		im.samplerName = samplerName;
		_imgs.push_back(im);
		return _imgs.back();

	}
};

