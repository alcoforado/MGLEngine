#include <MGLEngine.Shared/Resources/FreeTypeLoader.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <stdexcept>

void Require(bool condition, const char* message)
{
	if (!condition) throw std::runtime_error(message);
}
template<class F> void RequireThrows(F action)
{
	bool threw = false;
	try { action(); } catch (const std::exception&) { threw = true; }
	Require(threw, "Expected an exception");
}
int main(int argc, char** argv)
{
	try {
		Require(argc == 2, "Pass a font path");
		FreeTypeLoader loader;
		auto atlas = loader.Load(argv[1], 48, {}, 128);
		ITexImage& image = atlas->Image;
		Require(image.data && image.texChannels == 4 && image.texHeight > 48, "Invalid atlas image");
		Require(atlas->metadata.Characters.size() == 95, "Expected printable ASCII");
		const auto& space = atlas->metadata.Characters.at(U' ');
		Require(space.AdvanceX > 0 && space.Width == 0, "Whitespace metrics lost");
		auto pixels = static_cast<const uint8_t*>(image.data);
		bool hasCoverage = false;
		for (const auto& [ch, g] : atlas->metadata.Characters) {
			Require(g.X >= 1 && g.Y >= 1 && g.X + g.Width < image.texWidth &&
				g.Y + g.Height < image.texHeight, "Glyph outside padded atlas");
			Require(g.U0 <= g.U1 && g.V0 <= g.V1 && g.U1 <= 1 && g.V1 <= 1, "Invalid UVs");
			for (int y = 0; y < g.Height; ++y)
				for (int x = 0; x < g.Width; ++x)
					hasCoverage |= pixels[(static_cast<size_t>(g.Y + y) * image.texWidth + g.X + x) * 4 + 3] != 0;
		}
		Require(hasCoverage, "Empty bitmap");
		Require(pixels[0] == 255 && pixels[3] == 0, "Padding should be transparent white");
		FT_Library lib{};
		FT_Face face{};
		Require(!FT_Init_FreeType(&lib), "FreeType init failed");
		Require(!FT_New_Face(lib, argv[1], 0, &face), "Font open failed");
		FT_Set_Pixel_Sizes(face, 0, 48);
		Require(atlas->metadata.HasKerning == (FT_HAS_KERNING(face) != 0), "Kerning flag mismatch");
		size_t pairs = 0;
		for (const auto& [left, l] : atlas->metadata.Characters)
			for (const auto& [right, r] : atlas->metadata.Characters) {
				FT_Vector expected{};
				Require(!FT_Get_Kerning(face, l.GlyphIndex, r.GlyphIndex, FT_KERNING_DEFAULT, &expected),
					"Kerning lookup failed");
				auto actual = atlas->metadata.GetKerning(left, right);
				Require(actual.X == expected.x / 64.0f && actual.Y == expected.y / 64.0f, "Kerning mismatch");
				if (expected.x || expected.y) ++pairs;
			}
		Require(pairs == atlas->metadata.Kerning.size(), "Sparse kerning mismatch");
		FT_Done_Face(face);
		FT_Done_FreeType(lib);
		auto unicode = loader.Load(argv[1], 32, U"AA\u00e9\U0010ffff");
		Require(unicode->metadata.Characters.size() == 2 && unicode->metadata.Characters.contains(U'\u00e9'),
			"Unicode selection/deduplication failed");
		RequireThrows([&] { loader.Load("missing-font-file.ttf"); });
		RequireThrows([&] { loader.Load(argv[1], 0); });
		RequireThrows([&] { loader.Load(argv[1], 48, U"W", 3); });
		RequireThrows([&] { loader.Load(argv[1], 48, U"\U0010ffff"); });
		RequireThrows([&] { loader.Load(argv[1], 48, std::u32string(1, 0xD800)); });
		std::cout << "Font loader checks passed; " << pairs << " kerning pairs\n";
		return 0;
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
}

