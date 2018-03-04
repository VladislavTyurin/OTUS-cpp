#include <vector>
#include <string>
#include <fstream>

class LogWriter
{
public:
    void Write(std::vector<std::string>&);
    void setTimeStamp(std::string&);
private:
    void PrintVector();
    std::string LogName = "bulk";
    std::string TimeStamp = "";
};
