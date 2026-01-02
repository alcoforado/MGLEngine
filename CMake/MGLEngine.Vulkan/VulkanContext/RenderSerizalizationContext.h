#include <MGLEngine.Shared/Interfaces/IRenderSerializationContext.h>
#include <MGLEngine.Shared/Shaders/BindingManager.h>
class RenderSerializationContext : public IRenderSerializationContext {


public:
	RenderSerializationContext(void *pVerticeBuffer,uint32_t sizeVerticeInBytes, void *pIndexBuffer,uint32_t sizeIndexInBytes,BindingManager& binding) 
	{

	}

	InterleavedMemoryStream& GetVerticeAttribute(std::string name) override;
	IndicesMemoryStream& GetIndicesStream() override;
};