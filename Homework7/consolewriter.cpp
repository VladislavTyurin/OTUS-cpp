#include "consolewriter.h"

void ConsoleWriter::Write(std::vector<std::string>& bulk)
{
    for(auto&& element:bulk)
    {
        std::cout<<element<<" ";
    }
    std::cout<<std::endl;
}

void FileWriter::Write(std::vector<std::string>& bulk)
{
    std::ofstream out("bulk"+timestamp+".log");
    for(auto&& element:bulk)
    {
        out<<element<<" ";
    }
    out<<std::endl;
}

void FileWriter::setTimestamp(std::string t)
{
    timestamp=t;
}
