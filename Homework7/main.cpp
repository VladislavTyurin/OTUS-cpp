#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <memory>

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
    virtual ~Writer(){};
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
        console_writer.reset( new ConsoleWriter() );
        file_writer.reset( new FileWriter() );
    }

    ~StringHandler()
    {
        delete b;
    }

    void Run()
    {
        std::string command;
        while(std::getline(std::cin,command))
        {
            if(command=="{")
            {
                if(num_commands)
                {
                    DoWrite();
                    num_commands=0;
                }
                ++depth;
                continue;
            }

            if(command=="}")
            {
                --depth;
                if(depth==0)
                {
                    DoWrite();
                }
                continue;
            }

            b->ReadCommand(command);

            if(depth==0)
            {
                if(++num_commands==block_size_)
                {
                    DoWrite();
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
                Write(console_writer.get());
                Write(file_writer.get());
            }
        }
    }

private:
    int depth = 0;
    int block_size_;
    int num_commands = 0;

    Bulk* b;
    std::unique_ptr<Writer> console_writer;
    std::unique_ptr<Writer> file_writer;

    void DoWrite()
    {
        Write(console_writer.get());
        Write(file_writer.get());
        b->Reset();
    }

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
