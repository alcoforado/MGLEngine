#pragma once
#include <vector>
#include <string>
#include <MGLEngine.Shared/Utils/ovector.h>

class ImageConfig {
	friend class ShapeRegistrationConfig;
public:
	std::string filePath;

	~ImageConfig() {

	}
};

class ShapeRegistrationConfig
{
	
	ovector<ImageConfig> _imgs;

public:
	ShapeRegistrationConfig()
	{
	}


	ImageConfig& RegisterImage(std::string path)
	{
		ImageConfig im;
		im.filePath = path;
		_imgs.push_back(&im);
		return *(_imgs.back());
	}
};

