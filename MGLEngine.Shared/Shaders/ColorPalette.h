#pragma once

#include <glm/vec4.hpp>

// Normalized RGBA colors. RGB values use sRGB encoding; alpha is always 1.
class ColorPalette final {
public:
	ColorPalette() = delete;

	inline static const glm::vec4 Black{ 0.0f, 0.0f, 0.0f, 1.0f };
	inline static const glm::vec4 White{ 1.0f, 1.0f, 1.0f, 1.0f };
	inline static const glm::vec4 Gray{ 128.0f / 255.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f };
	inline static const glm::vec4 LightGray{ 211.0f / 255.0f, 211.0f / 255.0f, 211.0f / 255.0f, 1.0f };
	inline static const glm::vec4 DarkGray{ 64.0f / 255.0f, 64.0f / 255.0f, 64.0f / 255.0f, 1.0f };

	inline static const glm::vec4 Red{ 1.0f, 0.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Green{ 0.0f, 1.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Blue{ 0.0f, 0.0f, 1.0f, 1.0f };
	inline static const glm::vec4 Yellow{ 1.0f, 1.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Cyan{ 0.0f, 1.0f, 1.0f, 1.0f };
	inline static const glm::vec4 Magenta{ 1.0f, 0.0f, 1.0f, 1.0f };

	inline static const glm::vec4 Orange{ 1.0f, 165.0f / 255.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Purple{ 128.0f / 255.0f, 0.0f, 128.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Pink{ 1.0f, 192.0f / 255.0f, 203.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Brown{ 165.0f / 255.0f, 42.0f / 255.0f, 42.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Gold{ 1.0f, 215.0f / 255.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Coral{ 1.0f, 127.0f / 255.0f, 80.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Teal{ 0.0f, 128.0f / 255.0f, 128.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Navy{ 0.0f, 0.0f, 128.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Olive{ 128.0f / 255.0f, 128.0f / 255.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Maroon{ 128.0f / 255.0f, 0.0f, 0.0f, 1.0f };
	inline static const glm::vec4 Indigo{ 75.0f / 255.0f, 0.0f, 130.0f / 255.0f, 1.0f };
	inline static const glm::vec4 Violet{ 238.0f / 255.0f, 130.0f / 255.0f, 238.0f / 255.0f, 1.0f };
	inline static const glm::vec4 SkyBlue{ 135.0f / 255.0f, 206.0f / 255.0f, 235.0f / 255.0f, 1.0f };
};
