#pragma once
class MWindow;
class ResourceManager;
class MGLContainer {
private:
	MWindow* _pWindow;
	ResourceManager* _pRes;
public:
	
	MGLContainer(MWindow* pw, ResourceManager* res)
		:_pWindow(pw),_pRes(res)
	{

	}
	
	MWindow& GetWindow() { return *_pWindow; }
	ResourceManager& GetResourceManager() { return *_pRes; }




};