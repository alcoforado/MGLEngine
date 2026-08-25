#pragma once
#include <string>

class Tracer {
private:
    int get_terminal_width(int default_width = 80);
    std::string getIndent();
    int indent;
    int indent_size = 4;
    bool SectionStarted;
    bool TraceStarted;
    int _currentCol;
public:
    void Section(std::string message);
    void EndSection(std::string message);
    void Trace(std::string message);
    void Success();
    void Error();
};



