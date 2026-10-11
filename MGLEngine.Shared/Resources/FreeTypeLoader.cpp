#include <MGLEngine.Shared/Resources/FreeTypeLoader.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <algorithm>
#include <cstddef>
#include <set>
#include <stdexcept>

namespace {
	void CheckFreeType(FT_Error error, const std::string& operation)
	{
		if (error)
			throw std::runtime_error(operation + " (FreeType error " + std::to_string(error) + ")");
	}
	struct Library {
		FT_Library Handle = nullptr;
		Library() { CheckFreeType(FT_Init_FreeType(&Handle), "Initializing FreeType"); }
		~Library() { FT_Done_FreeType(Handle); }
	};
	struct Face {
		FT_Face Handle = nullptr;
		~Face() { if (Handle) FT_Done_Face(Handle); }
	};
	struct RasterGlyph {
		char32_t Character;
		FontGlyph fontGlyph;
		std::vector<uint8_t> Coverage;
	};
}

FontKerning FontAtlasMetadata::GetKerning(char32_t left, char32_t right) const
{
	auto it = Kerning.find({ left, right });
	return it == Kerning.end() ? FontKerning{} : it->second;
}

std::shared_ptr<FontAtlas> FreeTypeLoader::Load(const std::string& path,
	unsigned int pixelHeight, std::u32string_view characters, unsigned int atlasWidth) const
{
	constexpr int maxDimension = 16384;
	if (!pixelHeight || pixelHeight > maxDimension || atlasWidth < 3 || atlasWidth > maxDimension)
		throw std::invalid_argument("Invalid font pixel height or atlas width");

	Library library;
	Face face;
	CheckFreeType(FT_New_Face(library.Handle, path.c_str(), 0, &face.Handle), "Loading font '" + path + "'");
	CheckFreeType(FT_Select_Charmap(face.Handle, FT_ENCODING_UNICODE), "Selecting Unicode charmap");
	CheckFreeType(FT_Set_Pixel_Sizes(face.Handle, 0, pixelHeight), "Setting font size");

	std::set<char32_t> requested(characters.begin(), characters.end());
	if (characters.empty())
		for (char32_t ch = U' '; ch <= U'~'; ++ch) requested.insert(ch);

	auto atlas = std::make_shared<FontAtlas>();
	atlas->metadata.PixelHeight = pixelHeight;
	atlas->metadata.Ascender = face.Handle->size->metrics.ascender / 64.0f;
	atlas->metadata.Descender = face.Handle->size->metrics.descender / 64.0f;
	atlas->metadata.LineHeight = face.Handle->size->metrics.height / 64.0f;
	atlas->metadata.HasKerning = FT_HAS_KERNING(face.Handle) != 0;
	std::vector<RasterGlyph> glyphs;
	uint8_t  padding = 2;
	unsigned int x = padding, y = padding, biggestCharHeightInRow = 0; //x y is top left
	for (char32_t ch : requested) {
		auto index = FT_Get_Char_Index(face.Handle, static_cast<FT_ULong>(ch));
		if (!index) 
			continue;
		CheckFreeType(FT_Load_Glyph(face.Handle, index, FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL),
			"Rasterizing character " + std::to_string(static_cast<uint32_t>(ch)));
		
		auto slot = face.Handle->glyph;
		const auto& cbitmap = slot->bitmap;
		if (cbitmap.width > atlasWidth - 2*padding || cbitmap.rows > maxDimension - 2*padding)
			throw std::runtime_error("Font glyph exceeds atlas dimensions");
		unsigned int cwidth = cbitmap.width;
		unsigned int cheight = cbitmap.rows;
		if (x + cwidth + padding > atlasWidth) { //breakline
			x = padding;
			y += biggestCharHeightInRow + padding;
			biggestCharHeightInRow = 0;  //start checking again the bigger char in the line
		}
		if (y + cheight + 1 > maxDimension)
			throw std::runtime_error("Font atlas exceeds maximum height; request fewer characters");
		RasterGlyph glyph{ ch, {}, {} };
		auto& fontGlyph = glyph.fontGlyph;
		fontGlyph.GlyphIndex = index;
		fontGlyph.X = x; 
		fontGlyph.Y = y;
		fontGlyph.Width = cwidth; 
		fontGlyph.Height = cheight;
		fontGlyph.BearingX = slot->bitmap_left; 
		fontGlyph.BearingY = slot->bitmap_top;
		fontGlyph.AdvanceX = slot->advance.x / 64.0f; 
		fontGlyph.AdvanceY = slot->advance.y / 64.0f;
		glyph.Coverage.resize(cwidth * cheight);
		for (size_t row = 0; row < cheight; ++row) {
			const auto* src = cbitmap.buffer + row * cbitmap.pitch;
			for (int col = 0; col < cwidth; ++col) {
				uint8_t coverage;
				if (cbitmap.pixel_mode == FT_PIXEL_MODE_GRAY && cbitmap.num_grays > 1)
					coverage = static_cast<uint8_t>(src[col] * 255u / (cbitmap.num_grays - 1));
				else if (cbitmap.pixel_mode == FT_PIXEL_MODE_MONO) //PIXEL PER BIT
					coverage = (src[col / 8] & (0x80 >> (col % 8))) ? 255 : 0;
				else
					throw std::runtime_error("Unsupported FreeType bitmap format");
				glyph.Coverage[row * cwidth + col] = coverage;
			}
		}
		glyphs.push_back(std::move(glyph));
		x += cwidth + padding;
		biggestCharHeightInRow = (std::max)(biggestCharHeightInRow, cheight);
	}
	if (glyphs.empty()) throw std::runtime_error("Font contains none of the requested characters");
	atlas->Image.texWidth = atlasWidth;
	atlas->Image.texHeight = y + biggestCharHeightInRow + padding;
	atlas->Image.format = ImageFormat::R8;
	
	//Lets start writing the pixels with all the glyps we collected so far
	auto& pixels=atlas->pixels;
	pixels.resize(atlas->Image.texWidth * atlas->Image.texHeight);
	for (auto& glyph : glyphs) {
		//Now the we know the size of our image, We can calculate textures coordinates
		auto& c = glyph.fontGlyph;
		c.U0 = static_cast<float>(c.X) / atlas->Image.texWidth;
		c.V0 = static_cast<float>(c.Y) / atlas->Image.texHeight;
		c.U1 = static_cast<float>(c.X + c.Width) / atlas->Image.texWidth;
		c.V1 = static_cast<float>(c.Y + c.Height) / atlas->Image.texHeight;
		for (int row = 0; row < c.Height; ++row)
			for (int col = 0; col < c.Width; ++col)
				pixels[(c.Y + row) * atlas->Image.texWidth + c.X + col]
					= glyph.Coverage[row * c.Width + col];
		atlas->metadata.Characters.emplace(glyph.Character, c);
	}
	if (atlas->metadata.HasKerning)
		for (const auto& [left, l] : atlas->metadata.Characters)
			for (const auto& [right, r] : atlas->metadata.Characters) {
				FT_Vector delta{};
				CheckFreeType(FT_Get_Kerning(face.Handle, l.GlyphIndex, r.GlyphIndex, FT_KERNING_DEFAULT, &delta),
					"Reading font kerning");
				if (delta.x || delta.y)
					atlas->metadata.Kerning.emplace(std::make_pair(left, right), FontKerning{ delta.x / 64.0f, delta.y / 64.0f });
			}
	atlas->Image.data = pixels.data();
	return atlas;
}

