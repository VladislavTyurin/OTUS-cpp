#include <iostream>
#include "bulk.h"

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    int file_threads = 2;
    Bulk b(N,file_threads);
    std::string cmd;
    //std::getline(std::cin,cmd);
    while(std::getline(std::cin,cmd))
        b.ReadCommands(cmd);
    b.Report();
    return 0;
}