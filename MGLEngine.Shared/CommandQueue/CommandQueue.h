#pragma once
#include <vector>
#include <concepts>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <typeinfo>
#include <MGLEngine.Shared/Shaders/Std140Types.h>


class SetBufferCommand   {

public:
	std::vector<std::byte> vData;
		unsigned int binding;
	size_t size;
	size_t type_id;

};


class MGLEngine;
class CommandQueue {
	friend class MGLEngine;
private:
	std::vector<SetBufferCommand> _uboCommands;
public:
	template<typename T>
	void SetUbo(unsigned  binding, const T& data)
	{
		static_assert(std::derived_from<T, std140>, "UBO types must publicly inherit from std140 and explicitly match the shader layout.");
		static_assert(!std::is_same_v<T, std140>, "Use a concrete std140 data type, not the marker itself.");
		static_assert(std::is_trivially_copyable<T>::value, "Initializable type must be Trivially Copyable to use with DeclareMappedUbo!");
		static_assert(std::is_standard_layout_v<T>, "UBO types must have a standard layout.");
		
		
		
		_uboCommands.push_back(SetBufferCommand{
				.binding = binding,
			.size = sizeof(T),
			.type_id = typeid(T).hash_code()
		});

		auto& buffer = _uboCommands.back().vData; 

		buffer.resize(sizeof(T));
		std::memcpy(buffer.data(), &data, sizeof(T));
	}


};
