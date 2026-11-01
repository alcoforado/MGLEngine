#pragma once
#include <vector>
#include <MGLEngine.Shared/Resources/ResourceManager.h>




class MGLEngine;




class CommandDispatcher {
	friend class MGLEngine;
private:
	ResourceManager& _resourceManager;

	CommandQueue _queues;

	CommandDispatcher(ResourceManager& res)
		:_resourceManager(res) {
	};

	const CommandQueue& GetCommandQueues()  const {
		return _queues;
	}

public:
	
	template<typename T>
	void SetUbo(unsigned  binding, const T& data)
	{
		static_assert(std::derived_from<T, std140>, "UBO types must publicly inherit from std140 and explicitly match the shader layout.");
		static_assert(!std::is_same_v<T, std140>, "Use a concrete std140 data type, not the marker itself.");
		static_assert(std::is_trivially_copyable<T>::value, "Initializable type must be Trivially Copyable to use with DeclareMappedUbo!");
		static_assert(std::is_standard_layout_v<T>, "UBO types must have a standard layout.");
		
		
		auto& uboBinding = _resourceManager.GetGlobalBindingsTable()->GetUboBinding(binding);
		eassert(uboBinding.sizeOfDataType == sizeof(T), "Ubo write command has incompatible sizes");
		eassert(uboBinding.typeIndex == typeid(T).hash_code(), "Ubo write command has incompatible types");

		
		_queues.uboCommands.push_back(BufferWriteCommand{
			.glId = uboBinding.glId
		});

		auto& buffer = _queues.uboCommands.back().vData; 
		buffer.resize(sizeof(T));
		std::memcpy(buffer.data(), &data, sizeof(T));
	}


};