#include "eassert.h"
#include <boost/stacktrace.hpp>
AssertionFailureException::AssertionFailureException(std::string expression, std::string  file, int line, std::string message)
	: _expression(expression)
	, _file(file)
	, _line(line)
	, _message(message)

{
	boost::stacktrace::stacktrace st;
	
	_report = std::format("Error on {} line {}: Assert({}) => {}\n{}", file, line, expression, message,boost::stacktrace::to_string(st));

}

