#pragma once
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

struct FontGlyph {
	unsigned int GlyphIndex = 0;
	// Rectangle and UVs measured from the top-left of the atlas.
	int X = 0, Y = 0, Width = 0, Height = 0;
	float U0 = 0, V0 = 0, U1 = 0, V1 = 0;
	//BearingX is the horizontal offset from the pen position to the bitmap’s left edge :
	int BearingX = 0, 
		BearingY = 0;
	float AdvanceX = 0, 
		  AdvanceY = 0;
};

struct FontKerning {
	float X = 0, Y = 0;
};

// Glyph layout and kerning data, plus ownership of the atlas pixel storage.
class FontAtlasMetadata {
	friend class FreeTypeLoader;
public:
	std::map<char32_t, FontGlyph> Characters;
	// Sparse pairs; absent pairs have zero adjustment. Metrics are in pixels.
	std::map<std::pair<char32_t, char32_t>, FontKerning> Kerning;
	bool HasKerning = false;
	unsigned int PixelHeight = 0;
	float Ascender = 0, Descender = 0, LineHeight = 0;
	FontKerning GetKerning(char32_t left, char32_t right) const;
};

// Owns white RGBA pixels with coverage in alpha via metadata.
// Keep this object alive while using Image.data.


class FontAtlas  {
public:
	ITexImage image;
	FontAtlasMetadata metadata;
	std::vector<uint8_t> pixels;
	
	void DisposeBitmap() {
		pixels.clear();
		image.data = nullptr;
	}
};
class FreeTypeLoader {
public:
	// Empty characters selects printable ASCII (U+0020 to U+007E).
	// Missing glyphs are omitted. Invalid inputs and FreeType errors throw.
	s_ptr<FontAtlas> Load(const std::string& path,
		unsigned int pixelHeight = 48, std::u32string_view characters = {},
		unsigned int atlasWidth = 1024) const;
};

