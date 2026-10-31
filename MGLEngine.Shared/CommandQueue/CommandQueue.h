#pragma once


class SetUnfiformCommandBase {
public:
	void* pData;
	
};

template<class T>
class SetUniformCommand : public SetUnfiformCommandBase {
	
public:
	T data;

};