#pragma once
#include <string>
#include <list>
#include <variant>
#include <MGLEngine.Shared/Utils/eassert.h>
enum ResourceType
{
	IMAGE = 0,
	ATLAS=1,
	FREE_TYPE_FONT=2
};

struct FontData {
	uint32_t PixelHeight;
};

class ImageConfig {
	friend class ShapeRegistrationConfig;
private:
	std::variant<FontData> _extraData; //only
public:
	std::string filePath;
	std::string samplerName;
	ResourceType type;
	~ImageConfig() {

	}
	FontData GetFontData() {
		eassert(type == ResourceType::FREE_TYPE_FONT,"Image Resource is not a font");
		return std::get<FontData>(_extraData);
	}
};



class   ShapeRegistrationConfig
{
	
	std::list<ImageConfig> _imgs;

public:
	ShapeRegistrationConfig()
	{
	}

	std::list<ImageConfig>& GetImageAssignments() { return _imgs; }

	void BindImage(std::string path,std::string samplerName) 
	{
		ImageConfig im;
		im.filePath = path;
		im.type = ResourceType::IMAGE;
		im.samplerName = samplerName;
		_imgs.push_back(im);
		

	}

	void BindFont(std::string path, std::string samplerName,uint32_t pixelSize)
	{
		ImageConfig im;
		im.filePath = path;
		im.type = ResourceType::FREE_TYPE_FONT;
		im._extraData = FontData{
			.PixelHeight = pixelSize 
		};
		
		im.samplerName = samplerName;
		_imgs.push_back(im);
	}
};

