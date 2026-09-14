
#pragma once
#include <MGLEngine.Shared/utils.h>
#include <string>
#include <filesystem>
struct TexImage {
	void* data;
	int texWidth;
	int texHeight;
	int texChannels;

	TexImage() {
		texWidth = texHeight = texChannels = 0;
		data = nullptr;
	}

	~TexImage() {
		if (data!=nullptr)
			delete data;
	}
};

class ImageLoader {

	std::filesystem::path _base_path;
private:
	std::string GetFullPath(std::string relPath);
public:
	ImageLoader(std::string basePath = "");
	s_ptr<TexImage> LoadAsRGBA(std::string path);
	


};