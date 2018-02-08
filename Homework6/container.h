#pragma once

#include <iostream>
#include <algorithm>
#include <set>

#include "generate_tuple.h"
#include "tuple_forward.h"

template<typename T,int N,T default_value>
class IContainer
{
public:
    virtual ~IContainer(){};
    virtual void AddElement(std::pair<typename generate_tuple_type<int,N>::type,T>) = 0;
    virtual void Print() = 0;
    virtual void DeleteElement(typename generate_tuple_type<int,N>::type _tup) = 0;
};

template<typename T,T default_value>
class IContainer<T,2,default_value>
{
public:
    virtual ~IContainer(){};
    virtual void AddElement(std::pair<std::tuple<int,int>,T>) = 0;
    virtual void Print() = 0;
    virtual size_t Size() = 0;
    virtual void DeleteElement(std::tuple<int,int>) = 0;
    virtual void PrintFragment(int x1, int y1, int x2, int y2) = 0;
private:
    virtual T GetValue(int x, int y) = 0;
};

template <typename T, int N,T default_value>
class MatrixElementContainer:public IContainer<T,N,default_value>
{
public:

    void AddElement(std::pair<typename generate_tuple_type<int,N>::type, T> p) override
    {
        v.emplace(p);
    }

    void DeleteElement(typename generate_tuple_type<int,N>::type _tup) override
    {
        auto pos = std::find_if(v.begin(),v.end(),[&_tup](std::pair<typename generate_tuple_type<int,N>::type, T> p)->bool
        {
            return _tup==p.first;
        });
        if(pos!=v.end())
            v.erase(pos);
    }

    void Print() override
    {
        for(auto el:v)
        {
            print_tuple(el.first);
            std::cout<<el.second<<std::endl;
        }
    }

    size_t Size() override
    {
        return v.size();
    }

private:
    std::set<std::pair<typename generate_tuple_type<int,N>::type,T>> v;
};

template <typename T,T default_value>
class MatrixElementContainer<T,2,default_value>:public IContainer<T,2,default_value>
{
public:

    void AddElement(std::pair<std::tuple<int,int>, T> p) override
    {
        v.emplace(p);
    }

    void DeleteElement(std::tuple<int,int> _tup) override
    {
        auto pos = std::find_if(v.begin(),v.end(),[&_tup](std::pair<std::tuple<int,int>, T> p)->bool
        {
            return _tup==p.first;
        });
        if(pos!=v.end())
            v.erase(pos);
    }

    void Print() override
    {
        for(auto el:v)
        {
            print_tuple(el.first);
            std::cout<<el.second<<std::endl;
        }
    }

    void PrintFragment(int x1, int y1, int x2, int y2) override
    {
        for(int i=x1; i<=x2;++i)
        {
            for(int j=y1;j<=y2;++j)
            {
                std::cout<<GetValue(i,j);
                std::cout<<" ";
            }
            std::cout<<std::endl;
        }
    }

    size_t Size() override
    {
        return v.size();
    }

private:

    T GetValue(int x, int y) override
    {
        auto pos = std::find_if(v.begin(),v.end(),[&x,&y](std::pair<std::tuple<int,int>,T> p)->bool
        {
            return (std::get<0>(p.first)==x && std::get<1>(p.first)==y);
        });
        if(pos==v.end())
            return default_value;
        else
            return pos->second;
    }

    std::set<std::pair<std::tuple<int,int>,T>> v;
};