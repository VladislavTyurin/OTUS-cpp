#pragma once

#include <iostream>
#include <algorithm>
#include <map>

#include "generate_tuple.h"
#include "tuple_forward.h"

template<typename T,int N,T default_value>
class IContainer
{
public:
    virtual ~IContainer(){};
    virtual void AddElement(std::pair<typename generate_tuple_type<int,N>::type,T>) = 0;
    virtual void Print() = 0;
    virtual size_t Size() = 0;
    virtual void DeleteElement(typename generate_tuple_type<int,N>::type _tup) = 0;
    virtual T Value(typename generate_tuple_type<int,N>::type _tup)=0;
};

template <typename T, int N,T default_value>
class MatrixElementContainer:public IContainer<T,N,default_value>
{
public:

    void AddElement(std::pair<typename generate_tuple_type<int,N>::type, T> _p) override
    {
        auto pos = std::find_if(v.begin(),v.end(),[&_p](std::pair<typename generate_tuple_type<int,N>::type, T> p)->bool
        {
            return _p.first==p.first;
        });
        if(pos==v.end())
        {
            v.emplace(_p);
            return;
        }
        pos->second = _p.second;
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

    T Value(typename generate_tuple_type<int,N>::type _tup) override
    {
        //auto pos = std::find(v.begin(),v.end(),_tup);
        auto pos = v.find(_tup);
        if(pos!=v.end())
        {
            return v[_tup];
        }
        return default_value;
    }

    size_t Size() override
    {
        return v.size();
    }

private:
    std::map<typename generate_tuple_type<int,N>::type,T> v;
};