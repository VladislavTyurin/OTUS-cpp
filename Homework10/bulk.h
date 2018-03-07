#include "consolewriter.h"
#include <thread>
#include <functional>

struct WrapThread
{
    std::thread t;
    std::string name;
    int block_counter = 0;
    int cmd_counter = 0;
    int total_cmd=0;
};

class Bulk
{
public:
    Bulk(int _n, int num_threads = 1):n(_n){
        log.name="Log";
        for(int i=0;i<num_threads;++i)
        {
            file_threads.emplace_back(new WrapThread);
            file_threads.back()->name="File"+std::to_string(i+1);
        }
    };
    void ReadCommands(std::string cmd);
    void WriteCommands();
    void Report();

private:
    WrapThread log;
    std::vector<WrapThread*> file_threads;
    void ProcessThread(WrapThread&);
    std::deque<std::string> bulk;
    std::vector<char> brackets;
    std::string timestamp = "";
    bool firstCmd=true;
    int n;

    int num_blocks=0;
    int num_commands=0;
    int num_str=0;


   Writer* consoleWriter = new ConsoleWriter();
   Writer* fileWriter = new FileWriter();
};

template <class T, void (T::*method)(std::deque<std::string>, int&, int&)>
void wrap_func(void* pObj,std::deque<std::string> bulk, int& block_counter, int& cmd_counter)
{
    T *obj = static_cast<T *>(pObj);
    (obj->*method)(bulk,block_counter,cmd_counter);
}