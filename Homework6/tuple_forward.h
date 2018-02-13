#pragma once

#include <tuple>
#include <iostream>


template <int index, typename... Args>
struct iterate_tuple
{
    static void next(std::tuple<Args...>& t)
    {
        iterate_tuple<index-1,Args...>::next(t);
        std::cout<<std::get<index>(t);
    }
};

//Печать первого элемента
template <typename... Args>
struct iterate_tuple<0,Args...>
{
    static void next(std::tuple<Args...>& t)
    {
        std::cout<<std::get<0>(t);
    }
};

template <typename ...Args>
void print_tuple(std::tuple<Args...> t)
{
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;

    iterate_tuple<t_size-1, Args...>::next(t);
};
