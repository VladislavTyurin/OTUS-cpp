#include "bulk.h"

void Bulk::ReadCommands(std::string command)
{
    ++num_str;
    if(firstCmd)
    {
        timestamp = std::to_string(std::time(nullptr));
        firstCmd = false;
    }
    if(command=="{")
    {
        brackets.push_back('{');
        if(brackets.size()==1)
        {
            ++num_blocks;
            WriteCommands();
        }
        return;
    }
    else if(command=="}")
    {
        brackets.pop_back();
        if(brackets.size()==0)
        {
            ++num_blocks;
            WriteCommands();
        }
        return;
    }
    bulk.push_back(command);
    ++num_commands;
    if(bulk.size()==n && brackets.empty())
    {
        ++num_blocks;
        WriteCommands();
        return;
    }
}

void Bulk::WriteCommands()
{
    dynamic_cast<FileWriter*>(fileWriter)->setTimestamp(timestamp);
    dynamic_cast<FileWriter*>(fileWriter)->CreateFile();

    log.t = std::thread(wrap_func<ConsoleWriter,&ConsoleWriter::Write>,
                        consoleWriter,bulk,
                        std::ref(log.block_counter),
                        std::ref(log.cmd_counter));
    for(auto&& file:file_threads)
    {
        file->t = std::thread(wrap_func<FileWriter,&FileWriter::Write>,
                              fileWriter,bulk,
                              std::ref(file->block_counter),
                              std::ref(file->cmd_counter));
    }

    log.t.join();
    log.total_cmd+=log.cmd_counter;
    log.cmd_counter=0;

    for(auto&& file:file_threads)
    {
        file->t.join();
        file->total_cmd+=file->cmd_counter;
        file->cmd_counter=0;
    }

    timestamp.clear();
    firstCmd=true;
    bulk.clear();
}

void Bulk::Report()
{
    std::cout<<"main - "<<num_str<<" strings "<<num_commands<<" commnads "<<num_blocks<<" blocks\n";
    std::cout<<log.name<<" - "<<log.block_counter<<" blocks "<<log.total_cmd<<" commands"<<std::endl;
    for(auto&& file:file_threads)
    {
        std::cout<<file->name<<" -  "<<file->block_counter<<" blocks "<<file->total_cmd<<" commands"<<std::endl;
    }
}