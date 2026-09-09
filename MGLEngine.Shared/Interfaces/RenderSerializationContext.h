#pragma once
#include <map>
#include <string>
#include <format>
#include <MGLEngine.Shared/Utils/Arrays/InterleavedMemoryStream.h>
#include <MGLEngine.Shared/Utils/Arrays/IndicesMemoryStream.h>
class RenderSerializationContext  {
	std::map<std::string, InterleavedMemoryStream>& _vStreams;
	IndicesMemoryStream& _iStream;
public:
	RenderSerializationContext(std::map<std::string, InterleavedMemoryStream>& vStreams, IndicesMemoryStream& iStream)
		:_vStreams(vStreams), _iStream(iStream)
	{

	}

	InterleavedMemoryStream& GetVerticeAttribute(std::string name) 
	{
		eassert(_vStreams.find(name) != _vStreams.end(), std::format("No vertice attribute with name {} found in the shader context", name));
		return _vStreams[name];
	}
	IndicesMemoryStream& GetIndicesStream()  {
		return _iStream;
	}
};