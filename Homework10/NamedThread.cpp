#include "NamedThread.h"

void NamedThread::SetHandler(std::function<void()> func)
{
    t=std::thread(func);
}

std::string NamedThread::GetName() const
{
    return Name;
}

void NamedThread::Handler(Writer* writer, std::condition_variable& cv, std::mutex& cv_m, std::deque<Bulk>& bulk_queue, bool& done)
{
    std::unique_lock<std::mutex> lk(cv_m);

    if (done) {
        lk.unlock();
        return;
    }

    cv.wait(lk);

    if (!bulk_queue.empty())
    {
        auto bulk = bulk_queue.front();
        bulk_queue.pop_front();
        lk.unlock();
        block++;
        commands += bulk.Size();
        writer->Write(std::move(bulk));
    }
    else
        lk.unlock();
}

void NamedThread::Join()
{
    t.join();
}

std::thread& NamedThread::GetThread()
{
    return t;
}

const int NamedThread::GetCommands() const
{
    return commands;
}
const int NamedThread::GetBlocks() const
{
    return block;
}
