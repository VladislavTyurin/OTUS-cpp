#include "consolewriter.h"

void ConsoleWriter::Write(std::deque<std::string> bulk, int& block_counter, int& cmd_counter)
{
    ++block_counter;
    for(auto&& element:bulk)
    {
        std::cout<<element<<" ";
        ++cmd_counter;
    }
    std::cout<<std::endl;
}

void FileWriter::Write(std::deque<std::string> bulk,int& block_counter, int& cmd_counter)
{
    while(index<=bulk.size())
    {
        mtx.lock();
        if(index==bulk.size()) {
            mtx.unlock();
            break;
        }
        file<<bulk[index]<<" ";
        index++;
        file.seekp(current+bulk[index].size()+1);
        current+=bulk[index].size()+1;
        cmd_counter++;
        mtx.unlock();
    }
    if(cmd_counter)
        block_counter++;
}

void FileWriter::setTimestamp(std::string t)
{
    timestamp=t;
}

void FileWriter::CreateFile()
{
    file=std::ofstream("bulk"+timestamp+".log");
    index=0;
    current=0;
}
