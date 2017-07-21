#pragma once


template<class T>
class Listener
{
	void (*_handler)(T& t);
public:
	Listener(void(*handler)(T& t))
	{
		_handler = handler;
	}

	void Execute(T& t)
	{
		_handler(t);
	}




};

template<class T>
class Observable
{
	friend class Listener<T>;
public:
	Observable();
	~Observable();
	AddListener(Listener<T> &listener)
};

