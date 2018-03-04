#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>


class Writer
{
public:
    virtual void Write(std::vector<std::string>&) = 0;
};

class ConsoleWriter:public Writer
{
public:
    void Write(std::vector<std::string>&) override;
};

class FileWriter:public Writer
{
public:
    void Write(std::vector<std::string>&) override;
    void setTimestamp(std::string);
private:
    std::string timestamp;
};
