#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <thread>
#include <mutex>
#include <deque>

class Writer
{
public:
    virtual void Write(std::deque<std::string>, int&, int&) = 0;
};

class ConsoleWriter:public Writer
{
public:
    void Write(std::deque<std::string>, int&, int&) override;
};

class FileWriter:public Writer
{
public:
    void Write(std::deque<std::string>, int&, int&) override;
    void setTimestamp(std::string);
    void CreateFile();
private:
    std::ofstream file;
    std::string timestamp;
    std::mutex mtx;
    bool done;
    int index=0;
    int current=0;
};
