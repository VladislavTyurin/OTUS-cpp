#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <fstream>
#include <chrono>
#include <ctime>
#include <string>

class Bulk
{
public:
    void ReadCommand(std::string command);
    void Reset();
    void ConsoleWrite();
    void WriteFile();
    const int Size() const;

private:
    std::string timestamp="";
    bool first_command=true;
    std::vector<std::string> commands;
    int unique_num = 0;
};
