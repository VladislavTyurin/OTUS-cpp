#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <random>
#include <chrono>

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

class Writer
{
public:
    virtual void Write(Bulk*) = 0;
};

class ConsoleWriter:public Writer
{
public:
    void Write(Bulk* b) override
    {
        b->ConsoleWrite();
    }
};

class FileWriter:public Writer
{
public:
    void Write(Bulk* b) override
    {
        b->WriteFile();
    }
};

class StringHandler
{
public:
    StringHandler() = delete;
    StringHandler(int block_size, int num_threads=1):block_size_(block_size)
    {
        b=new Bulk();
        console_writer = new ConsoleWriter();
        file_writer = new FileWriter();
    }

    ~StringHandler()
    {
        delete b;
        delete console_writer;
        delete file_writer;
    }

    void Run()
    {
        std::string command;
        while(std::getline(std::cin,command))
        {
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
                    Write(console_writer);
                    Write(file_writer);
                    b->Reset();
                }
                continue;
            }

            b->ReadCommand(command);

            if(depth==0)
            {
                if(++num_commands==block_size_)
                {
                    Write(console_writer);
                    Write(file_writer);
                    b->Reset();
                    num_commands=0;
                    continue;
                }
            }
        }
    }

    void Stop()
    {
        if(depth == 0)
        {
            if(num_commands)
            {
                Write(console_writer);
                Write(file_writer);
            }
        }
    }

private:
    int depth = 0;
    int block_size_;
    int num_commands = 0;

    Bulk* b;
    Writer* console_writer;
    Writer* file_writer;

    void Write(Writer* writer)
    {
        writer->Write(b);
    }

};

int main(int argc, char* argv[])
{
    int block_size = atoi(argv[1]);

    StringHandler handler(block_size);
    handler.Run();
    handler.Stop();
    return 0;
}
