#pragma once


#include <iostream>
#include <string>
#include <algorithm>

const std::string WHITESPACE = " \n\r\t\f\v";

inline std::string ltrim(const std::string& s, std::string trimChars=WHITESPACE)
{
	size_t start = s.find_first_not_of(trimChars);
	return (start == std::string::npos) ? "" : s.substr(start);
}

inline std::string rtrim(const std::string& s, std::string trimChars = WHITESPACE)
{
	size_t end = s.find_last_not_of(trimChars);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

inline std::string trim(const std::string& s,std::string trimChars=WHITESPACE)
{
	return rtrim(ltrim(s,trimChars),trimChars);

}


inline bool delimitedBy(std::string str1, const std::string& start, const std::string& end)
{
	return (str1.find_first_of(start) == 0 && str1.find_last_of(end) == (str1.length() - 1));
	
}

inline bool hasPrefix(std::string prefix, std::string str)
{
	return memcmp(prefix.c_str(),str.c_str(),prefix.size()*sizeof(std::string::value_type))==0;
}