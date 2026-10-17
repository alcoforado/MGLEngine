#pragma once
#include <map>
#include <string>
#include <format>
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/Arrays/InterleavedMemoryStream.h>
#include <MGLEngine.Shared/Utils/Arrays/IndicesMemoryStream.h>

class FontAtlasMetadata;
class ResourceManager;
class RenderSerializationContext  {
	std::map<std::string, InterleavedMemoryStream>& _vStreams;
	IndicesMemoryStream& _iStream;
	ResourceManager& _res;
	glm::vec2 _windowSize;
public:
	RenderSerializationContext(std::map<std::string, InterleavedMemoryStream>& vStreams, IndicesMemoryStream& iStream,ResourceManager &res,glm::vec2 windowSizeInPixels)
		:_vStreams(vStreams), _iStream(iStream), _res(res)
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