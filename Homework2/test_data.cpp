#include "test_data.h"
#include "ip_filter.cpp"

std::vector<std::string> test_data()
{
    std::vector<std::string> v;
    std::vector<VecStr > ip_pool;
    std::string ip="";
    for(int i=1;i<5;++i)
    {
        for(int j=1;j<5;++j)
        {
            for(int k=1;k<5;++k)
            {
                for(int l=1;l<5;++l)
                {
                    ip = std::to_string(i)+"."+std::to_string(j)+"."+std::to_string(k)+"."+std::to_string(l);
                    v.push_back(ip);
                }
            }
        }
    }

    for(auto ip = v.rbegin();ip!=v.rend();++ip)
    {
        ip_pool.push_back(ip);
    }
    return ip_pool;
}