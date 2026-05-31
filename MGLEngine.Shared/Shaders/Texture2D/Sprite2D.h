#pragma once
#include <MGLEngine.Shared/Interfaces/IMGLEngine.h>

class Sprite2D {
	float width, height;
	glm::vec2 bl;
	public:
		Sprite2D(IMGLEngine& engine, glm::vec2 bl, float width, float height,std::string imgPath)
			:width(width),height(height),bl(bl)
		{
			engine.RegisterTexture(imgPath);
		}



};