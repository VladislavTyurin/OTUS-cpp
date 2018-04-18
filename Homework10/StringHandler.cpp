#include "StringHandler.h"

StringHandler::StringHandler(int block_size, int num_threads):block_size_(block_size),num_threads_(num_threads)
{
    b.reset(new Bulk());
    console_writer.reset(new ConsoleWriter());
    file_writer.reset(new FileWriter());
    logs.reset(new ThreadPool(1,"log"));
    files.reset(new ThreadPool(num_threads_,"file"));
    logs->SetHandler(console_writer.get(),done);
    files->SetHandler(file_writer.get(),done);
};

void StringHandler::Run()
{
    std::string command;
    while(std::getline(std::cin,command))
    {
        string_counter++;
        if(command=="{")
        {
            if(num_commands)
            {
                AddBulkToQueue();
                DoWrite();
                blocks_counter++;
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
                AddBulkToQueue();
                DoWrite();
                blocks_counter++;
            }
            continue;
        }

        b->ReadCommand(command);
        command_counter++;

        if(depth==0)
        {
            if(++num_commands==block_size_)
            {
                AddBulkToQueue();
                DoWrite();
                num_commands=0;
                blocks_counter++;
                continue;
            }
        }
    }

    if(depth == 0)
    {
        AddBulkToQueue();
        DoWrite();
        blocks_counter++;
    }

    DoWriteRest();
}

void StringHandler::Stop()
{
    done = true;
    logs->Stop();
    files->Stop();
}

void StringHandler::Report()
{
    logs->Join();
    files->Join();
    std::cout<<"main: "<<string_counter<<" strings "<<command_counter<<" commands "<<blocks_counter<<" blocks\n";
    logs->Report();
    files->Report();
}

void StringHandler::AddBulkToQueue()
{
    logs->AddToDeque(b.get());
    files->AddToDeque(b.get());
    b->Reset();
}

void StringHandler::DoWrite()
{
    logs->DoWrite();
    files->DoWrite();
}

void StringHandler::DoWriteRest()
{
    logs->DoWriteRest();
    files->DoWriteRest();
}
