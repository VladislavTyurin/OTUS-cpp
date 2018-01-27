#pragma once

#include <tuple>
#include <iostream>

//Печать внутренних элементов
struct callback
{
    template <typename T>
    void operator()(T&& t)
    {
        std::cout<<"."<<t;
    }
};

template <bool is_same_type,int index, typename Callback, typename... Args>
struct iterate_tuple
{
    static bool next(std::tuple<Args...>& t, Callback callback)
    {
        constexpr bool state = std::is_same<decltype(std::get<index>(t)), decltype(std::get<index-1>(t))>::value;
        //Если типы двух соседних элементов равны, то проходим по кортежу дальше
        if(iterate_tuple<state, index-1, Callback, Args...>::next(t,callback))
        {
            callback(std::get<index>(t));
            return true;
        }
        return false;
    }
};

//Печать первого элемента
template <typename Callback, typename... Args>
struct iterate_tuple<true,0, Callback, Args...>
{
    static bool next(std::tuple<Args...>& t, Callback callback)
    {
        std::cout<<std::get<0>(t);
        return true;
    }
};

//Ошибка типов (разные типы)
template <int index, typename Callback, typename... Args>
struct iterate_tuple<false, index, Callback, Args...>
{
    static bool next(std::tuple<Args...>& t, Callback callback)
    {
        std::cout<<"Type error";
        return false;
    }
};

template <typename Callback, typename ...Args>
void for_each(std::tuple<Args...>& t, Callback callback)
{
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;
    //Первый аргумент отвечает за типы, если true - все типы одинаковые
    iterate_tuple<true,t_size-1,Callback, Args...>::next(t,callback);
    std::cout<<std::endl;
};
