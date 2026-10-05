#include <string>



const std::string WHITESPACE = " \n\r\t\f\v";

std::string Trim(std::string str)
{
    size_t start = str.find_first_not_of(WHITESPACE);
    str.erase(0, start);
    size_t end = str.find_last_not_of(WHITESPACE);
    str.erase(end + 1);
    return str;
}

std::string ReplaceFirst(std::string src, std::string textToFind, std::string textToReplace)
{
    size_t pos = src.find(textToFind);
    if (pos != std::string::npos)
    {
        return src.replace(pos, textToFind.length(), textToReplace);
    }
    else
    {
        return src;
    }
}
