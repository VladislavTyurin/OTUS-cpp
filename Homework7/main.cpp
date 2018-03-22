#include "bulk.h"

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    Bulk b(N);
    std::string cmd;
    //std::getline(std::cin,cmd);
    while(std::getline(std::cin,cmd))
        b.ReadCommands(cmd);

    if(b.GetBracketsSize()==0) {
        b.WriteCommands();
    }
}
