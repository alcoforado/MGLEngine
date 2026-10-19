#include <MGLEngine.Shared/Interfaces/RenderSerializationContext.h>
#include <MGLEngine.Shared/Resources/ResourceManager.h>
#include <MGLEngine.Shared/Window/MWindow.h>

const FontAtlasMetadata& RenderSerializationContext::GetFontMetadata(std::string samplerName)
{
	return _mglContainer.GetResourceManager().GetFontMetadata(samplerName);
}


glm::vec2 RenderSerializationContext::WindowSize()
{
	auto size=_mglContainer.GetWindow().Size();
	return glm::vec2(size.width, size.height);
}
