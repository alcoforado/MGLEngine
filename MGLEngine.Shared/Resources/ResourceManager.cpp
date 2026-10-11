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

Resource ResourceManager::Load(ImageRef& imgRef)
{
	ITexImage texImage;
	switch (imgRef.type)
	{
		case ResourceType::IMAGE:
		{
			auto img = _imgLoader.LoadAsRGBA(GetFullPath(imgRef.filePath));
			auto glId=_gl.LoadTexture(*img);
			return Resource{
				.glid = glId,
				.MetadataId = 0
			};
		}

	}
	return Resource();
}