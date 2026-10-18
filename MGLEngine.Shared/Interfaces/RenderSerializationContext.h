#pragma once
#include <map>
#include <string>
#include <format>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/Arrays/InterleavedMemoryStream.h>
#include <MGLEngine.Shared/Utils/Arrays/IndicesMemoryStream.h>

class FontAtlasMetadata;
class ResourceManager;

struct WindowData {
	uint32_t width;
	uint32_t height;
};

struct MGLData {
	ResourceManager& manager;
	WindowData window;
};


class RenderSerializationContext  {
	std::map<std::string, InterleavedMemoryStream>& _vStreams;
	IndicesMemoryStream& _iStream;
	MGLData _mglData;
	glm::vec2 _windowSize;
public:
	RenderSerializationContext(std::map<std::string, InterleavedMemoryStream>& vStreams, IndicesMemoryStream& iStream,MGLData& data)
		:_vStreams(vStreams), _iStream(iStream), _mglData(data)
	{

	}

	glm::vec2 WindowSize() {

	}

	InterleavedMemoryStream& GetVerticeAttribute(std::string name) 
	{
		eassert(_vStreams.find(name) != _vStreams.end(), std::format("No vertice attribute with name {} found in the shader context", name));
		return _vStreams[name];
	}
	IndicesMemoryStream& GetIndicesStream()  {
		return _iStream;
	}

	const FontAtlasMetadata& GetFontMetadata(std::string samplerName);


};