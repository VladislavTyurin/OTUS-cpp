#pragma once

#include "ThreadPool.h"

using ThreadVector = std::vector<NamedThread>;

class StringHandler
{
public:
    StringHandler() = delete;
    StringHandler(int block_size, int num_threads=1);
    void Run();
    void Stop();
    void Report();

private:

    int string_counter=0;
    int command_counter=0;
    int blocks_counter=0;

    int depth = 0;
    int block_size_;
    int num_threads_;
    int num_commands = 0;
    bool done = false;

    std::unique_ptr<ThreadPool> logs;
    std::unique_ptr<ThreadPool> files;
    std::unique_ptr<Bulk> b;
    std::unique_ptr<Writer> console_writer;
    std::shared_ptr<Writer> file_writer;

    void AddBulkToQueue();
    void DoWrite();
    void DoWriteRest();
};