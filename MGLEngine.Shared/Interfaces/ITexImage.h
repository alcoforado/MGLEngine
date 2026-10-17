enum ImageFormat {
	R8G8B8A8 = 0,
	R8 = 1
};

struct ITexImage {
	void* data;
	unsigned int texWidth;
	unsigned int texHeight;
	unsigned int texChannels;
	ImageFormat format;
};

