#pragma once

#include <vector>

template<class T>
class PoolBuffer
{
	std::vector<T*> _pool;
	int _i;;

public:
	
	virtual T* createNew() = 0;


	PoolBuffer()
	{
		
		_i = 0;
	}

	T* GetNext()
	{
		
		if (_i < _pool.size() )
		{
			return _pool[_i++];
		}
		else
		{
			
			_pool.push_back(createNew());
			return _pool[_i++];
		}
	}

	void ReleaseAll()
	{
		_i = 0;
	}

	~PoolBuffer()
	{
		for(T* elem: _pool)
		{
			delete elem;
		}
	}
};