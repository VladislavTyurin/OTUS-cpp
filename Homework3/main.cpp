#include <iostream>
#include <map>

#include "map_allocator.h"
#include "my_container.h"

template <typename T>
T factorial(T n)
{
    T res=1;
    for(T i=n;i>0;--i)
        res*=i;
    return res;
}

int main()
{
    const int n=10;
    std::map<int,int> standart_m;

    for(int i=0;i<n;++i)
    {
        standart_m.emplace(std::pair<int,int>(i,factorial(i)));
    }

    std::map<int,int,std::less<int>,map_allocator<std::pair<int,int >,n > > m;

    for(int i=0;i<n;++i)
    {
        m.emplace(std::pair<int,int>(i,factorial(i)));
    }

    for(auto&& p:m)
    {
        std::cout<<p.first<<" "<<p.second<<std::endl;
    }

    MyContainer<int> standart_p;

    for(int i=0;i<n;++i)
    {
        standart_p.push_back(i);
    }

    MyContainer<int,map_allocator<int,n>> p;

    for(int i=0;i<n;++i)
    {
        p.push_back(i);
    }

    for(auto&& el:p)
    {
        std::cout<<el<<std::endl;
    }
    //p.forward();
    return 0;
}