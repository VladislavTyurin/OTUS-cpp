#include "StringHandler.h"
#include <cstdlib>

int main(int argc, char* argv[])
{
    int block_size = atoi(argv[1]);

    StringHandler handler(block_size);
    handler.Run();
    handler.Stop();
    return 0;
}
