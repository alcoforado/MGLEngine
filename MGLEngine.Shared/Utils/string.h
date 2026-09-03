#include "string.h"

const std::string WHITESPACE = " \n\r\t\f\v";

std::string Trim(std::string str)
{
    size_t start = str.find_first_not_of(WHITESPACE);
    str.erase(0, start);
    size_t end = str.find_last_not_of(WHITESPACE);
    str.erase(end + 1);
    return str;
}
