#pragma once
#include <vector>
#include <concepts>
template <typename T>
class ovector : public std::vector<T*>
{
public:
	ovector() {}

	ovector(const ovector<T*>& copy)
	{
		for (auto pElem : copy)
		{
			T* pNew = new T();
			*pNew = *pElem;
			this->push_back(pNew);
		}
	}

	

	~ovector() {
		for (auto p : *this)
		{
			delete p;
		}
		
	}
};