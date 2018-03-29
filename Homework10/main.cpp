#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <condition_variable>
#include <fstream>
#include <map>

class Bulk
{
public:

    void ReadCommand(std::string command)
    {
        if(first_command)
        {
            timestamp = std::to_string(std::time(nullptr));
            first_command = false;
        }

        commands.push_back(command);
    }

    void Reset()
    {
        commands.clear();
        first_command=true;
    }

    void ConsoleWrite()
    {
        std::cout<<"bulk:";
        for(auto&& command:commands)
        {
            std::cout<<" "<<command;
        }
        std::cout<<std::endl;
    }

    void WriteFile()
    {
        std::string filename = "bulk"+timestamp+".log";
        std::ofstream ofs(filename);
        ofs<<"bulk:";
        for(auto&& command:commands)
        {
            ofs<<" "<<command;
        }
        ofs.close();
    }

    int Size()
    {
        return commands.size();
    }

private:
    std::string timestamp="";
    bool first_command=true;
    std::vector<std::string> commands;
};

class NamedThread
{
public:
    NamedThread(std::string name_, std::function<void()> func):Name(name_)
    {
        t = std::thread(func);
    }

    std::string GetName() const
    {
        return Name;
    }

    void Join()
    {
        t.join();
    }

    std::thread& GetThread()
    {
        return t;
    }

private:
    std::thread t;
    std::string Name;
};

struct Counter
{
    int commands=0;
    int block=0;
};


class StringHandler
{
public:
    StringHandler() = delete;
    StringHandler(int block_size, int num_threads=1):block_size_(block_size),num_threads_(num_threads)
    {
        b=new Bulk();

        tv.emplace_back(NamedThread("log",[this](){
            this->WriteBulkToConsole();
        }));


        for(int i=0;i<num_threads_;++i)
        {
            std::string thread_name = "file"+std::to_string(i+1);
            tv.emplace_back(NamedThread(thread_name,[this](){
               this->WriteBulk();
            }));

        }
    };

    ~StringHandler()
    {
        for(auto& t :tv)
        {
            t.Join();
        }
        delete b;
    }

    void Run()
    {
        std::string command;
        while(std::getline(std::cin,command))
        {
            string_counter++;
            if(command=="{")
            {
                ++depth;
                continue;
            }

            if(command=="}")
            {
                --depth;
                if(depth==0)
                {
                    {
                        std::lock_guard<std::mutex> lk(cv_m);
                        bulk_queue.emplace_back(*b);
                    }
                    {
                        std::lock_guard<std::mutex> lk(log_cv_m);
                        console_bulk_queue.emplace_back(*b);
                    }
                    b->Reset();
                    blocks_counter++;
                    cv.notify_one();
                    log_cv.notify_one();
                }
                continue;
            }

            b->ReadCommand(command);
            command_counter++;

            if(depth==0)
            {
                if(++num_commands==block_size_)
                {
                    {
                        std::lock_guard<std::mutex> lk(cv_m);
                        bulk_queue.emplace_back(*b);
                    }
                    {
                        std::lock_guard<std::mutex> lk(log_cv_m);
                        console_bulk_queue.emplace_back(*b);
                    }
                    b->Reset();
                    num_commands=0;
                    cv.notify_one();
                    log_cv.notify_one();
                    blocks_counter++;
                    continue;
                }
            }
        }
    }

    void Stop()
    {
        if(depth == 0)
        {
            if(num_commands) {
                bulk_queue.emplace_back(*b);
                console_bulk_queue.emplace_back(*b);
            }
            while(console_bulk_queue.size()) {
                log_cv.notify_one();
            }
            while(bulk_queue.size()) {
                cv.notify_one();
            }
        }
        done = true;
        cv.notify_all();
        log_cv.notify_all();
    }

    void Report()
    {
        for(int i=0;i<=num_threads_;++i)
        {
            std::cout<<tv[i].GetName()<<": "
                     <<tm[tv[i].GetThread().get_id()].block<<" blocks "
                     <<tm[tv[i].GetThread().get_id()].commands<<" commands"<<std::endl;
        }

    };

private:

    int string_counter=0;
    int command_counter=0;
    int blocks_counter=0;

    std::map<std::thread::id, Counter> tm;
    std::vector<NamedThread> tv;
    int depth = 0;
    int block_size_;
    int num_threads_;
    int num_commands = 0;
    bool done = false;

    std::condition_variable cv;
    std::mutex cv_m;

    std::condition_variable log_cv;
    std::mutex log_cv_m;

    Bulk* b;
    std::deque<Bulk> bulk_queue;
    std::deque<Bulk> console_bulk_queue;

    void WriteBulk()
    {
        while(!done )
        {
            std::unique_lock<std::mutex> lk(cv_m);
            this->cv.wait(lk);
            if(bulk_queue.size())
            {
                auto bulk = bulk_queue.front();
                bulk_queue.pop_front();
                lk.unlock();
                tm[std::this_thread::get_id()].block++;
                tm[std::this_thread::get_id()].commands+=bulk.Size();
                bulk.WriteFile();
                continue;
            }
            lk.unlock();
        }
    }

    void WriteBulkToConsole()
    {
        while(!done )
        {
            std::unique_lock<std::mutex> lk(log_cv_m);
            this->log_cv.wait(lk);
            if(console_bulk_queue.size())
            {
                auto bulk = console_bulk_queue.front();
                console_bulk_queue.pop_front();
                lk.unlock();
                tm[std::this_thread::get_id()].block++;
                tm[std::this_thread::get_id()].commands+=bulk.Size();
                bulk.ConsoleWrite();
                continue;
            }
            lk.unlock();
        }
    }
};

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