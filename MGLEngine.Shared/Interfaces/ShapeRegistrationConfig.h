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

class IShapeRegistrationConfig {
public:
	virtual ImageConfig& BindImage(std::string path, std::string samplerName) = 0;
};

class ShapeRegistrationConfig : public  IShapeRegistrationConfig
{
	
	std::list<ImageConfig> _imgs;

public:
	ShapeRegistrationConfig()
	{
	}

	std::list<ImageConfig>& GetImageAssignments() { return _imgs; }

	virtual ImageConfig& BindImage(std::string path,std::string samplerName) override
	{
		ImageConfig im;
		im.filePath = path;
		im.samplerName = samplerName;
		_imgs.push_back(im);
		return _imgs.back();

	}
};

