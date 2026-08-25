#include "Tracer.h"

#include <iostream>

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

// Returns the number of characters per line, or a fallback default if it fails
int Tracer::get_terminal_width(int default_width) {
#if defined(_WIN32)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	// Get the handle for the standard output screen buffer
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole != INVALID_HANDLE_VALUE && GetConsoleScreenBufferInfo(hConsole, &csbi)) {
		// Calculate width: right edge coordinate minus left edge coordinate + 1
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
#else
	struct winsize w;
	// Query the terminal driver via ioctl
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
		return w.ws_col;
	}
#endif

	// Return fallback if the output is redirected to a file or fails
	return default_width;
}

std::string Tracer::getIndent() {
	std::string result = "";
	int nSpaces = indent * indent_size;
	for (int i = 0; i < nSpaces; i++)
	{
		result += " ";
	}
	return result;
}

void Tracer::Trace(std::string message)
{
	if (TraceStarted)
	{
		std::cout << std::endl;
	}
	TraceStarted = true;
	std::string result = getIndent() + message;
	std::cout << result;
	_currentCol = result.length();
}

void Tracer::Success(std::string message)
{
	std::string result = "";
	if (TraceStarted)
	{
		int width = get_terminal_width();
		int nDots = width - _currentCol - 4;
		for (int i = 0; i < nDots; i++)
		{
			result += ".";
		};
		result += "[OK]";
		std::cout << result << std::endl;

	}
	TraceStarted = false;
}

void Tracer::Error(std::string message)
{
	std::string result = "";
	if (TraceStarted)
	{
		int width = get_terminal_width();
		int nDots = width - _currentCol - 4;
		for (int i = 0; i < nDots; i++)
		{
			result += ".";
		};
		result += "[Error]";
		std::cout << result << std::endl;

	}
	TraceStarted = false;
}






