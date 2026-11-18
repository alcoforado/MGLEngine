#include "MGLEngine.h"
#include <MGLEngine.Shared/Utils/pointers.h>
#include <MGLEngine.Shared/Utils/eassert.h>
#include <MGLEngine.Vulkan/VulkanEngineContainer.h>
#include<MGLEngine.Shared/Resources/ImageLoader.h>
#include <MGLEngine.Shared/Window/MWindow.h>
#include "Shaders/BindingConstants.h"
MGLEngine::MGLEngine(WindowOptions& wOptions, AppConfiguration& appConfig)
	:_appConfig(appConfig),
	_pWindow(s_new<MWindow>(wOptions)),
	_gl(*VulkanEngineContainer::GetLibrary(_pWindow, appConfig)),
	_resourceManager(_gl,appConfig.AssetsRootPath),
	_commandQueue(_resourceManager)
{
	std::cout << "Use Count " <<  _pWindow.use_count() << std::endl;
	_pMGLContainer = s_new<MGLContainer>(&(*_pWindow), &_resourceManager);
}

MGLEngine::~MGLEngine()
{
	std::cout << "Use Count " << _pWindow.use_count() << std::endl;
	delete &_gl;
	std::cout << "Use Count " << _pWindow.use_count() << std::endl;
}

void MGLEngine::WiringEvents()
{
	//Initialize Camera
	this->_camera.SetCamera(_appConfig._pos, _appConfig._lookAt, _appConfig._up);
	

	if (_resourceManager.GetGlobalBindingsTable()->HasUboBinding(UboBindingCollection::CameraTransform.binding))
	{
		this->OnCameraChange().Subscribe([this](const glm::mat4& matrix) {
			this->CommandDispatcher().SetUbo(
				UboBindingCollection::CameraTransform.binding,
				Std140Mat4(matrix)
			);
		});
	}
	this->_pCamInputMapping = s_new<CameraInputMapping>(_camera);
	s_ptr<EventListener<KeyboardEvent>> p = this->_pCamInputMapping;
	this->OnKeyboardPress().Subscribe(p);



}

void MGLEngine::Run()
{
	this->LoadShaders();
	
	

	//Wiring Events
	WiringEvents();

	auto glfwWindow = _pWindow->GLFWHandler();


	while (!_pWindow->ShouldClose())
	{
		_pWindow->PollEvents();
		this->frameTickEmitter.Emit();
		_gl.Draw(_shaders, *_pMGLContainer,_commandQueue.GetCommandQueues());
		_commandQueue.ClearQueue();
	}

}




bool MGLEngine::IsShaderRegistered(const std::type_index shaderType)
{
	return _shadersIndex.find(shaderType) != _shadersIndex.end();
}

void MGLEngine::LoadShaders()
{
	
	for (auto& shader : _shaders)
	{
		_resourceManager.RegisterShaderBindings(shader);
		_resourceManager.RegisterShapeResources(shader);
	}
	_resourceManager.LoadAllResources();
	_gl.LoadShaders(_shaders, *_pMGLContainer);
}






 