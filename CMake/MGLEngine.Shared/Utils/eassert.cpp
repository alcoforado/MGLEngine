#include "eassert.h"


std::ostream* AssertionFailureException::_pErrorOut = nullptr;

void AssertionFailureException::SetOutput(std::ostream* pErrorOut)
{
	_pErrorOut = pErrorOut;
}
