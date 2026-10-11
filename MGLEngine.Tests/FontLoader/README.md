Focused font loader checks, independent of the legacy engine/HTTP tests.
Run from an x64 Visual Studio developer shell at the repository root:

```powershell
cmake -S MGLEngine.Tests/FontLoader -B out/build/font-loader-tests -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=C:/Repo/vcpkg/scripts/buildsystems/vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_MSVC_RUNTIME_LIBRARY=MultiThreadedDebug -DFONT_TEST_FILE=C:/Windows/Fonts/times.ttf
cmake --build out/build/font-loader-tests
ctest --test-dir out/build/font-loader-tests --output-on-failure
```

Override the toolchain and font paths for your machine. The fixture font should
contain printable ASCII and U+00E9. The checks compare every loaded character
pair against FreeType, so both fonts with and without pair kerning work.

The loader defaults to printable ASCII at 48 pixels. Pass a UTF-32 character
set to load other glyphs; missing characters are omitted. The returned FontAtlas
owns its bitmap and exposes Image (ITexImage) for texture upload, metadata.Characters for layout,
and metadata.Kerning/GetKerning for pair adjustments in pixels. Atlas rows and UVs start
at the top-left. Bearings use FreeType's baseline convention (positive Y up).
Pixels are white RGBA with coverage in alpha and one transparent pixel of padding.
Kerning is FreeType pair kerning, not general OpenType shaping. Pair generation
is quadratic in the number of requested characters; request the set you need.

