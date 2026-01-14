#include <MGLEngine.Shared/Interfaces/IRenderSerializationContext.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>
#include <MGLEngine.Shared/Utils/Arrays/IndicesMemoryStream.h>
class RenderSerializationContext : public IRenderSerializationContext {
	std::map<std::string, InterleavedMemoryStream>& _vStreams;
	IndicesMemoryStream& _iStream;
public:
	RenderSerializationContext(std::map<std::string, InterleavedMemoryStream> &vStreams, IndicesMemoryStream &iStream )
		:_vStreams(vStreams),_iStream(iStream)
	{

	}

	InterleavedMemoryStream& GetVerticeAttribute(std::string name) override
	{
		return _vStreams[name];
	}
	IndicesMemoryStream& GetIndicesStream() override {
		return _iStream;
	}
};