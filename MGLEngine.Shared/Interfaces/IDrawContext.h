#pragma once
#include <cstdint>
#include <string>
#include <typeinfo>
class IDrawContext
{
	protected:
		virtual void _PushConstant(std::string varName, void* pData, size_t typeIndex, size_t sizeofT)=0;
	public:
		


		virtual void DrawIndexed()=0;

		template<typename T>
		void PushConstant(std::string varName, T data)
		{
			_PushConstant(varName, &data, typeid(T).hash_code(), sizeof(T));
		}

};