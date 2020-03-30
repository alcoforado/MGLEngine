#pragma once

#include <vector>
#include <list>

template<class T>
class PoolHandle;

template<class T>
class PoolBuffer
{
	friend class PoolHandle<T>;
	std::vector<T*> _allocated;
	std::list<PoolHandle<T>*> _handles;

protected:
	virtual T* createNew() = 0;

public:
	typedef typename PoolHandle<T> Handle;




	PoolHandle<T>* Allocate();

	virtual ~PoolBuffer()
	{
		for (auto h : _handles)
		{
			delete h->_data;
			h->_data = nullptr;
		}
		for (T* elem : _allocated)
		{
			delete elem;
		}
	}
};

template<class T>
class PoolHandle
{
	friend class PoolBuffer<T>;
private:
	T * _data;
	PoolBuffer<T> *_pool;
	PoolHandle(PoolBuffer<T> *pool)
	{
		_pool = pool;
		if (_pool->_allocated.size() == 0)
			_data = _pool->createNew();
		else
		{
			_data = _pool->_allocated.back();
			_pool->_allocated.pop_back();
		}
		_pool->_handles.push_back(this);
	}
public:
	T* GetResource()
	{
		return _data;
	}

	~PoolHandle()
	{
		if (_data != nullptr)
		{
			_pool->_allocated.push_back(_data);
			_data = nullptr;
		}
		_pool->_handles.remove_if([this](PoolHandle<T>*h) {return h == this; });
	}
};

template<class T>
PoolHandle<T>* PoolBuffer<T>::Allocate()
{
	return new PoolBuffer<T>::Handle(this);
}





