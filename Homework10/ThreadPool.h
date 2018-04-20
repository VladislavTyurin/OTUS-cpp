#pragma once

#include "NamedThread.h"

class ThreadPool
{
public:
    ThreadPool(int count, std::string name);
    void Join();
    void SetHandler(Writer* write, bool& done);
    void DoWrite();
    void DoWriteRest();
    void Stop();
    void Report();
    void AddToDeque(const Bulk* b);
private:

    bool GetQE();
    std::deque<Bulk> bulk_queue;
    std::vector<NamedThread> threads;
    std::condition_variable cv;
    std::mutex cv_m;
    bool QE;
};

