#include "StringHandler.h"

int main(int argc, char* argv[])
{
    int block_size = atoi(argv[1]);
    int num_threads = 2;

    StringHandler handler(block_size,num_threads);
    handler.Run();
    handler.Stop();
    handler.Report();
    return 0;
}