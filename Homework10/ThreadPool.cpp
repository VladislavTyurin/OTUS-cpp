#include "ThreadPool.h"

ThreadPool::ThreadPool(int count, std::string name)
{
    if(count>1)
    {
        for (int i = 0; i < count; ++i)
        {
            threads.emplace_back(NamedThread(name+std::to_string(i+1)));
        }
    }
    else
        threads.emplace_back(NamedThread(name));
}

void ThreadPool::Join()
{
    for(auto&& t:threads)
    {
        t.Join();
    }
}

void ThreadPool::SetHandler(Writer *writer, bool& done)
{
    for(auto&& t:threads)
    {
        t.SetHandler([&t,this, &done, writer]
                     {
                         while(!done)
                            t.Handler(writer, this->cv,this->cv_m, this->bulk_queue,done);
                     });
    }
}

void ThreadPool::DoWrite()
{
    cv.notify_one();
}

void ThreadPool::DoWriteRest()
{
    while(!QE)
    {
        cv.notify_one();
        QE=GetQE();
    }
}

void ThreadPool::Stop()
{
    cv.notify_all();
}

void ThreadPool::Report()
{
    for(auto&& t :threads)
    {
        std::cout<<t.GetName()<<": "
                 <<t.GetBlocks()<<" blocks "
                 <<t.GetCommands()<<" commands"<<std::endl;
    }
}

void ThreadPool::AddToDeque(const Bulk *b)
{
    std::lock_guard<std::mutex> lk(cv_m);
    bulk_queue.emplace_back(*b);
}

bool ThreadPool::GetQE()
{
    std::lock_guard<std::mutex> lk(cv_m);
    return bulk_queue.empty();
}