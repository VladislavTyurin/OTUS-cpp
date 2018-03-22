#include "consolewriter.h"

class Bulk
{
public:
    Bulk(int _n):n(_n){};
    void ReadCommands(std::string);
    void WriteCommands();
    int GetBracketsSize();

private:
    std::vector<std::string> bulk;
    std::vector<char> brackets;
    std::string timestamp = "";
    bool firstCmd=true;
    int n;

   Writer* consoleWriter = new ConsoleWriter();
   Writer* fileWriter = new FileWriter();
};
