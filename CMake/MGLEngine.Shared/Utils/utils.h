#include "eassert.h"

template<typename T>
void if_free(T* p) {
	if (p != nullptr)
		delete p;
};