#pragma once

#include <vector>
#include <list>
#include <deque>
#include "pointers.h"

template<class T>
class Pool
{

	class HandleData   {
		friend class Pool;
	private:
		Pool<T>* pool;
		size_t index;
		T* pData;
	public:
		T& Data() { return *pData; }

	};


	std::deque<T> _heap;
	std::deque<HandleData> _heapOfHandles;
	std::deque<size_t> _availableIndices;


public:


	typedef typename std::shared_ptr<HandleData> Handle;



	Handle Allocate()
	{
		HandleData* pResult=nullptr;
		if (_availableIndices.empty())
		{
			_heap.push_back(T());
			HandleData elem;
			elem.pool = this;
			elem.index = _heap.size()-1;
			elem.pData = &(_heap.back());
			_heapOfHandles.push_back(elem);
			pResult = &(_heapOfHandles.back());
			
		}
		else {
			size_t index = _availableIndices.front();
			_availableIndices.pop_front();
			pResult = &(_heapOfHandles[index]);

		}
		return std::shared_ptr<HandleData>(pResult, [this](HandleData* pHandle) {
			this->_availableIndices.push_back(pHandle->index);
		});
		 
	}

	

	
};

