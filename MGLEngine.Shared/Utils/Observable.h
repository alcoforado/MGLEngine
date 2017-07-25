#pragma once
#include <list>
#include <functional>

template <class T>
class Listener;


template<class T>
class Observable
{
	friend class Listener<T>;
	std::list<Listener<T>*> _list;
public:
	Observable() {};
	~Observable()
	{
		Dispose();
	}

	void Emit(T &t)
	{
		for (Listener<T>* listener : _list)
		{
			listener->Execute(t);
		}
	}

	void Dispose()
	{
		for (Listener<T>* listener : _list)
		{
			listener->DetachFromObserver(this);
		}
	}


};



template<class T>
class Listener
{
	std::list<Observable<T>*> _list;
	std::function<void(T t)> _handler;
public:
	Listener(std::function<void(T t)> handler)
	{
		_handler = handler;
	}

	void SetHandler(std::function<void(T t)> handler)
	{
		_handler = handler;
	}

	Listener()
	{
		_handler = nullptr;
	}


	void Execute(T t)
	{
		if (_handler)
			_handler(t);
	}
	
	~Listener()
	{
		Dispose();
	}


	void DetachFromObserver(Observable<T> *obs)
	{
		auto it = std::find(_list.begin(), _list.end(), obs);
		if (it != _list.end())
		{
			_list.erase(it);
			auto oIt = std::find(obs->_list.begin(),obs->_list.end(),this);
			if (oIt!=obs->_list.end())
			{
				obs->_list.erase(oIt);
			}
		}
	}

	void Listen(Observable<T> *obs)
	{
		auto it = std::find(_list.begin(), _list.end(), obs);
		if (it == _list.end())
		{
			_list.push_back(obs);
			auto oIt = std::find(obs->_list.begin(), obs->_list.end(), this);
			if (oIt == obs->_list.end())
			{
				obs->_list.push_back(this);
			}
		}
	}

	void Dispose()
	{
		while(!_list.empty())
		{
			this->DetachFromObserver(*_list.begin());
		}
	}

};

