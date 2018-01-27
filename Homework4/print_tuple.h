#pragma once

#include <tuple>
#include <iostream>

template <bool is_same_type,int index, typename Printer, typename... Args>
struct iterate_tuple
{
    static bool next(std::tuple<Args...>& t, Printer printer)
    {
        constexpr bool state = std::is_same<decltype(std::get<index>(t)), decltype(std::get<index-1>(t))>::value;
        //Если типы двух соседних элементов равны, то проходим по кортежу дальше
        if(iterate_tuple<state, index-1, Printer, Args...>::next(t,printer))
        {
            printer(std::get<index>(t),index);
            return true;
        }
        return false;
    }
};

//Печать первого элемента
template <bool state, typename Printer, typename... Args>
struct iterate_tuple<state,0, Printer, Args...>
{
    static bool next(std::tuple<Args...>& t, Printer printer)
    {
        //std::cout<<std::get<0>(t);
        printer(std::get<0>(t),0);
        return true;
    }
};

//Ошибка типов (разные типы)
template <int index, typename Printer, typename... Args>
struct iterate_tuple<false, index, Printer, Args...>
{
    static bool next(std::tuple<Args...>& t, Printer printer)
    {
        std::cerr<<"Type error";
        return false;
    }
};

/**
Рекурсивный обход кортежа с печатью элементов
- прямой проход - проверка типов
- обратный проход - печать элементов
 */
template <typename Printer, typename ...Args>
void print_tuple(std::tuple<Args...>& t, Printer printer)
{
    int const t_size = std::tuple_size<std::tuple<Args...>>::value;

    //Первый аргумент отвечает за типы, если true - все типы одинаковые
    iterate_tuple<true,t_size-1,Printer, Args...>::next(t,printer);
    std::cout<<std::endl;
};
