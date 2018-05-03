#include <iostream>

#include "async.h"

int main() {
    std::size_t bulk = 5;
    auto h = async::connect(bulk);
    auto h2 = async::connect(bulk-2);
    async::receive(h, "1", 1);
    async::receive(h2, "11\n", 2);
    async::receive(h, "\n2\n3\n4\n5\n6\n{\na\n", 15);
    async::receive( h2, "1\n11\n",4 );
    async::receive(h, "b\nc\nd\n}\n89\n", 11);
    async::receive( h2, "1\n11\n1\n11\n", 8 );
    async::disconnect(h);
    async::disconnect(h2);
    return 0;
}
