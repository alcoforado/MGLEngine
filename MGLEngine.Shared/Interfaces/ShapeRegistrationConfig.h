#pragma once
#include <string>
#include <list>

class ImageConfig {
	friend class ShapeRegistrationConfig;
public:
	std::string filePath;

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


	ImageConfig& RegisterImage(std::string path)
	{
		ImageConfig im;
		im.filePath = path;
		_imgs.push_back(im);
		return _imgs.back();
	}
};

