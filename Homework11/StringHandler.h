#pragma once

#include "Writer.h"
#include <memory>

class StringHandler
{
public:
    StringHandler(int block_size);
    void ReadCommand( std::string );
    void Stop();

private:
    int depth = 0;
    int block_size_=0;
    int num_commands = 0;

    std::unique_ptr<Bulk> b;
    std::unique_ptr<Writer> console_writer;
    std::unique_ptr<Writer> file_writer;

    void DoWrite();
    void Write(Writer* writer);
};