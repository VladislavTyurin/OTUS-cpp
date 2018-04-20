#include "StringHandler.h"

StringHandler::StringHandler(int block_size):block_size_(block_size)
{
    b.reset( new Bulk() );
    console_writer.reset( new ConsoleWriter() );
    file_writer.reset( new FileWriter() );
}

void StringHandler::Run()
{
    std::string command;
    while(std::getline(std::cin,command))
    {
        if(command=="{")
        {
            if(num_commands)
            {
                DoWrite();
                num_commands=0;
            }
            ++depth;
            continue;
        }

        if(command=="}")
        {
            --depth;
            if(depth==0)
            {
                DoWrite();
            }
            continue;
        }

        b->ReadCommand(command);

        if(depth==0)
        {
            if(++num_commands==block_size_)
            {
                DoWrite();
                num_commands=0;
                continue;
            }
        }
    }
}

void StringHandler::Stop()
{
    if(depth == 0)
    {
        if(num_commands)
        {
            Write(console_writer.get());
            Write(file_writer.get());
        }
    }
}

void StringHandler::DoWrite()
{
    Write(console_writer.get());
    Write(file_writer.get());
    b->Reset();
}

void StringHandler::Write(Writer* writer)
{
    writer->Write(b.get());
}
