#pragma once
template<class T>
class IMappedMemory
{
public:
	virtual void Flush() = 0;
	virtual IArray<T> Map() = 0;
	virtual VkBuffer GetHandle() const = 0;

	virtual ~IMappedMemory(){}
};



