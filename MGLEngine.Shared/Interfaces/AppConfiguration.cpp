#include "AppConfiguration.h"
#include <filesystem>
#include <MGLEngine.Shared/Utils/string.h>
AppConfiguration::AppConfiguration()
{
	AssetsRootPath = std::filesystem::current_path().string();
	_pos = { 2,2,2 };
	_lookAt = { 0,0,0 };
	_up = {0, 0, 1};


}

void AppConfiguration::ImagesRoot(std::string imageRootPath)
{
	if (imageRootPath.starts_with("./"))
	{
		AssetsRootPath=ReplaceFirst(imageRootPath, "./", std::filesystem::current_path().string() + "/");
	}
	AssetsRootPath = imageRootPath;
}
