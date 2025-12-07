#pragma once

#include <exception>
#include <string>
#include <sstream>
#include <iostream>
#include <format>
#define INVALID_INDEX -1
/// Exception type for assertion failures
class AssertionFailureException : public std::exception
{
private:
	std::string _file;
	int _line;
	std::string _message;
	std::string report;
	std::string _expression;
	std::string _report;
public:

	/// Construct an assertion failure exception
	AssertionFailureException(std::string expression, std::string  file, int line, std::string message);
	
	/// The assertion message
	virtual const char* what() const throw()
	{
		return _report.c_str();
	}

	~AssertionFailureException() throw()
	{
	}
};


/// Assert that EXPRESSION evaluates to true, otherwise raise AssertionFailureException with associated MESSAGE (which may use C++ stream-style message formatting)

#ifdef NDEBUG
	#define eassert(EXPRESSION, MESSAGE) ((void)0)
#else
	#define eassert(EXPRESSION, MESSAGE) if(!(EXPRESSION)) {  throw AssertionFailureException(#EXPRESSION, __FILE__, __LINE__, MESSAGE); }
#endif