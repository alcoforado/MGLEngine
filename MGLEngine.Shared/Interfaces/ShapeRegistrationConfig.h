#pragma once
#include <string>
#include <list>

enum ResourceType
{
	IMAGE = 0,
	ATLAS=1,
	FREE_TYPE_FONT=2
};



class ImageConfig {
	friend class ShapeRegistrationConfig;
public:
	std::string filePath;
	std::string samplerName;
	ResourceType type;
	~ImageConfig() {

	}
};

class IShapeRegistrationConfig {
public:
	virtual void BindImage(std::string path, std::string samplerName) = 0;
	virtual void BindFont(std::string path, std::string samplerName) = 0;
};

class ShapeRegistrationConfig : public  IShapeRegistrationConfig
{
	
	std::list<ImageConfig> _imgs;

public:
	ShapeRegistrationConfig()
	{
	}

	std::list<ImageConfig>& GetImageAssignments() { return _imgs; }

	virtual void BindImage(std::string path,std::string samplerName) override
	{
		ImageConfig im;
		im.filePath = path;
		im.type = ResourceType::IMAGE;
		im.samplerName = samplerName;
		_imgs.push_back(im);
		

	}

	virtual void BindFont(std::string path, std::string samplerName)
	{
		ImageConfig im;
		im.filePath = path;
		im.type = ResourceType::FREE_TYPE_FONT;
		im.samplerName = samplerName;
		_imgs.push_back(im);
	}
};

