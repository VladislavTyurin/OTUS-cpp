#include "logwriter.h"

void LogWriter::Write(std::vector<std::string>& bulk)
{

}

void LogWriter::setTimeStamp(std::string &timestamp)
{
    TimeStamp = timestamp;
}

void LogWriter::PrintVector(std::vector<std::string>& bulk)
{
    for(auto&& element:bulk)
    {
        std::cout<<element<<" ";
    }
    std::cout<<std::endl;
}
