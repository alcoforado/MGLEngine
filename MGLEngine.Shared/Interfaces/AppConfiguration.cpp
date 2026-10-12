#include "AppConfiguration.h"
#include <filesystem>
#include <MGLEngine.Shared/Utils/string.h>
AppConfiguration::AppConfiguration()
{
	AssetsRootPath = std::filesystem::current_path().string();

}

void AppConfiguration::ImagesRoot(std::string imageRootPath)
{
	if (imageRootPath.starts_with("./"))
	{
		AssetsRootPath=ReplaceFirst(imageRootPath, "./", std::filesystem::current_path().string() + "/");
	}
	AssetsRootPath = imageRootPath;
}
