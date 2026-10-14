#include <MGLEngine.Shared/Resources/ResourceManager.h>
#include <MGLEngine.Shared/Interfaces/IGraphicLibrary.h>

ResourceManager::ResourceManager(IGraphicLibrary& gl, std::string basePath)
	:_gl(gl),_base_path(basePath)
{

}

std::string ResourceManager::GetFullPath(std::string relPath)
{
	if (_base_path.empty())
		return relPath;
	else
		return (_base_path / std::filesystem::path(relPath)).string();
}

Resource ResourceManager::Load(ResourceRef& resRef)
{
	ITexImage texImage;
	switch (resRef.config.type)
	{
		case ResourceType::IMAGE:
		{
			auto img = _imgLoader.LoadAsRGBA(GetFullPath(resRef.config.filePath));
			auto glId=_gl.LoadTexture(*img);
			return Resource{
				.glid = glId,
				.MetadataId = 0
			};
		}
		case ResourceType::FREE_TYPE_FONT:
		{
			
			auto atlas = _freeTypeLoader.Load(GetFullPath(resRef.config.filePath), resRef.config.GetFontData().PixelHeight, {}, 256);
			auto glId = _gl.LoadTexture(atlas->image);
			atlas->DisposeBitmap();
			fontsMetadata.push_back(atlas);
			return Resource{
				.glid = glId,
				.MetadataId = fontsMetadata.size() - 1
			};
		}

	}
	return Resource();
}
