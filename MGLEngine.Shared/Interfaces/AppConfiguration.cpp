#include "AppConfiguration.h"
#include <filesystem>

AppConfiguration::AppConfiguration()
{
	ImageRootPath = std::filesystem::current_path().string();

}