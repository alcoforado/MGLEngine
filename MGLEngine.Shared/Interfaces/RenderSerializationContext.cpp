#include <MGLEngine.Shared/Interfaces/RenderSerializationContext.h>
#include <MGLEngine.Shared/Resources/ResourceManager.h>


const FontAtlasMetadata& RenderSerializationContext::GetFontMetadata(std::string samplerName)
{
	return _mglContainer.GetResourceManager().GetFontMetadata(samplerName);
}