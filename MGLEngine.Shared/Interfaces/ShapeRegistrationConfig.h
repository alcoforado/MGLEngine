#pragma once
#include <string>
#include <format>
#include <list>
#include <variant>
#include <MGLEngine.Shared/Utils/eassert.h>
enum ResourceType
{
	INVALID_TYPE=0,
	IMAGE = 1,
	ATLAS = 2,
	FREE_TYPE_FONT = 3
};

struct FontData {
	uint32_t PixelHeight;
};

class ResourceDeclaration {
	friend class ShapeRegistrationConfig;
private:
	std::variant<FontData> _extraData; //only
public:
	std::string filePath;
	std::string samplerName;
	ResourceType type;
	bool IsFont() { return type == ResourceType::FREE_TYPE_FONT; }

	ResourceDeclaration()
	{
		type = ResourceType::INVALID_TYPE;
	}
	~ResourceDeclaration() {

	}
	FontData GetFontData() {
		eassert(type == ResourceType::FREE_TYPE_FONT, "Image Resource is not a font");
		return std::get<FontData>(_extraData);
	}
	std::string UniqueId() const {
		switch (type)
		{
		case ResourceType::FREE_TYPE_FONT:
			return std::format("font {} {}", filePath, std::get<FontData>(_extraData).PixelHeight);

		case ResourceType::IMAGE:
			return std::format("image {}", filePath);
		default:
			throw_error("Resource Type not supported");
		}
	}
};



class   ShapeRegistrationConfig
{

	std::list<ResourceDeclaration> _res;

public:
	ShapeRegistrationConfig()
	{
	}

	const std::list<ResourceDeclaration>& GetResourceDeclarations() const { return _res; }

	void BindImage(std::string path, std::string samplerName)
	{
		ResourceDeclaration r;
		r.filePath = path;
		r.type = ResourceType::IMAGE;
		r.samplerName = samplerName;
		_res.push_back(r);


	}

	void BindFont(std::string path, std::string samplerName, uint32_t pixelSize)
	{
		ResourceDeclaration im;
		im.filePath = path;
		im.type = ResourceType::FREE_TYPE_FONT;
		im._extraData = FontData{
			.PixelHeight = pixelSize
		};

		im.samplerName = samplerName;
		_res.push_back(im);
	}
};

