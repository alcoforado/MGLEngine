#include "AppConfiguration.h"
#include <filesystem>
#include <MGLEngine.Shared/Utils/string.h>
AppConfiguration::AppConfiguration()
{
	ImageRootPath = std::filesystem::current_path().string();

}

void AppConfiguration::ImagesRoot(std::string imageRootPath)
{
	if (imageRootPath.starts_with("./"))
	{
		ImageRootPath=ReplaceFirst(imageRootPath, "./", std::filesystem::current_path().string() + "/");
	}
	ImageRootPath = imageRootPath;
}
