#include "bulk.h"

void Bulk::ReadCommands(std::string command)
{
    if(firstCmd)
    {
        timestamp = std::to_string(std::time(nullptr));
        firstCmd = false;
    }
    if(command=="{")
    {
        brackets.push_back('{');
        if(brackets.size()==1 && bulk.size())
        {
            WriteCommands();
        }
        return;
    }
    else if(command=="}")
    {
        brackets.pop_back();
        if(brackets.size()==0)
        {
            WriteCommands();
        }
        return;
    }
    bulk.push_back(command);
    if(bulk.size()==n && brackets.empty())
    {
        WriteCommands();
        return;
    }
}

void Bulk::WriteCommands()
{
    dynamic_cast<FileWriter*>(fileWriter)->setTimestamp(timestamp);
    consoleWriter->Write(bulk);
    fileWriter->Write(bulk);
    timestamp.clear();
    firstCmd=true;
    bulk.clear();
}

int Bulk::GetBracketsSize()
{
    return brackets.size();
}
