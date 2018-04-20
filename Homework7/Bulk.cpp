#include "Bulk.h"

void Bulk::ReadCommand(std::string command)
{
    if(first_command)
    {
        timestamp = std::to_string(std::time(nullptr));
        first_command = false;
    }

    commands.push_back(command);
}

void Bulk::Reset()
{
    commands.clear();
    first_command=true;
}

void Bulk::ConsoleWrite()
{
    std::cout<<"bulk:";
    for(auto&& command:commands)
    {
        std::cout<<" "<<command;
    }
    std::cout<<std::endl;
}

void Bulk::WriteFile()
{
    std::string filename = "bulk"+timestamp+".log";
    std::ofstream ofs(filename);
    ofs<<"bulk:";
    for(auto&& command:commands)
    {
        ofs<<" "<<command;
    }
    ofs.close();
}

const int Bulk::Size() const
{
    return commands.size();
}
