#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

using VecStr = std::vector<std::string>;
using TupleIp4 = std::tuple<int,int,int,int>; // Кортеж, содержащий значения Ipv4 адресов

void filter(const std::vector<VecStr>& ip_pool)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}

void filter_any(const std::vector<VecStr>& ip_pool, int ip_byte)
{
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        if(std::any_of(ip->cbegin(),ip->cend(),[&ip_byte](std::string s){return std::stoi(s) == ip_byte;}))
        {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part) {
                if (ip_part != ip->cbegin()) {
                    std::cout << ".";
                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

template <typename... Args>
void filter(const std::vector<VecStr >& ip_pool,Args... args)
{
    const int n = sizeof...(args);
    int index = 0;
    std::vector<int> v = {args...};
    for(auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        index = 0;
        std::string ip_address;
        for(auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if(index < n && stoi(*ip_part)!= v[index])
            {
                ip_address.clear();
                break;
            }
            if (ip_part != ip->cbegin())
            {
                ip_address+= ".";
            }

            ip_address+= *ip_part;
            ++index;
        }
        if(!ip_address.empty())
            std::cout<<ip_address<<std::endl;
    }
};

VecStr split(const std::string &str, char d)
{
    VecStr r;

    auto start = 0;
    auto stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

inline TupleIp4 make_ip_tuple(const VecStr& ip)
{
    return std::make_tuple(std::stoi(ip[0]),std::stoi(ip[1]),std::stoi(ip[2]),std::stoi(ip[3]));
}

int main(int argc, char const *argv[])
{
    try
    {
        std::vector<VecStr > ip_pool;
        for(std::string line; std::getline(std::cin, line);)
        {
            VecStr v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        //reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),[](const VecStr & ip1, const VecStr & ip2)
        {
            return make_ip_tuple(ip2)<make_ip_tuple(ip1);
        });

        filter(ip_pool);
        filter(ip_pool,1);
        filter(ip_pool,46,70);
        filter_any(ip_pool,46);

        //filter();
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
