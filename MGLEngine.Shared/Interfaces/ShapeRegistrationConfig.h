#pragma once
#include <MGLEngine.Shared/Interfaces/IDrawingObject.h>


class ShapeRegistrationConfig
{
	IDrawingObject* pObject;
	std::vector<ImageConfig> imgp;

public:
	ShapeRegistrationConfig(IDrawingObject* pobj) 

};

class ImageConfig {
	std::string filePath;
};