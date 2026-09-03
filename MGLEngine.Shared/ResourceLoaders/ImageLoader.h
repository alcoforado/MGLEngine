#include <MGLEngine.Shared/utils.h>
#include <string>
struct TexImage {
	void* data;
	int texWidth;
	int texHeight;
	int texChannels;

	TexImage() {
		*this = {};
		data = nullptr;
	}

	~TexImage() {
		if (data!=nullptr)
			delete data;
	}
};

class ImageLoader {


public:
	s_ptr<TexImage> LoadAsRGBA(std::string path);
	


};