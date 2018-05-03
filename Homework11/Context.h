#pragma once

#include "StringHandler.h"
#include <thread>
#include <condition_variable>
#include <deque>

class Context {
public:
    Context(const int bulk_size);
    ~Context();
    void Receive(const char* data, size_t size);
    void Stop();
private:
    void Waiting();
    void ParseData( const char* data );
    void HandleRest();
    bool GetQE();
    std::shared_ptr<StringHandler> string_handler;
    std::thread t;
    std::condition_variable cv;
    std::mutex cv_m;
    std::deque<std::string> deque_data;
    bool done=false;
    bool QE = false;
};

