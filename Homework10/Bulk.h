#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <thread>

class Bulk
{
public:
    void ReadCommand(std::string command);
    void Reset();
    void ConsoleWrite();
    void WriteFile();
    const int Size() const;
private:
    std::mt19937 engine;
    std::string timestamp="";
    bool first_command=true;
    std::vector<std::string> commands;
};

