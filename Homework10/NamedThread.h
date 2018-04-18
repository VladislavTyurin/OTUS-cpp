#pragma once

#include <deque>
#include "Writer.h"

class NamedThread
{
public:
    NamedThread(std::string name_):Name(name_) {}
    void SetHandler(std::function<void()> func);
    std::string GetName() const;
    void Handler(Writer* writer, std::condition_variable& cv, std::mutex& cv_m, std::deque<Bulk>& bulk_queue, bool& done);
    void Join();
    std::thread& GetThread();
    const int GetCommands() const;
    const int GetBlocks() const;
private:
    std::function<void()> func_;
    std::thread t;
    std::string Name;
    int commands=0;
    int block=0;
};