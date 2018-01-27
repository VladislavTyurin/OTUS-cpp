#include <iostream>
#include <utility>
#include <tuple>
#include <bitset>
#include <vector>
#include <list>
#include <functional>
#include "check_type.h"
#include "print_tuple.h"

//Функция печати
template <typename T>
void printer(T&& t, int index)
{
    if(index==0)
    {
        std::cout<<t;
        return;
    }
    std::cout<<"."<<t;
}

//Печать целочисленных типов
template <typename T>
void print(T t, int)
{
    auto p = std::bitset<8*sizeof(t)>(t).to_string();
    for(int i=0;i<sizeof(t);++i)
    {
        printer(std::bitset<8>(p,i*8,8).to_ulong(),i);
    }
    std::cout<<std::endl;
}

//Печать контейнеров
template <typename T>
void print(T t,char)
{
    auto start = t.cbegin();
    auto end = t.cend();
    int i=0;
    for(auto&& el:t)
    {
        printer(el,i++);
    }
    std::cout<<std::endl;
}

//Печать строки
void print(std::string t, char)
{
    std::cout<<t<<std::endl;
}

template <typename T>
void print_ip(T t)
{
    print(t,is_container<T>::value);
}

//Отдельная специализация для кортежа
template <typename... Args>
void print_ip(std::tuple<Args...> t)
{
    //Рекурсия: прямой проход - проверка типов
    //обратный проход - печать элементов
    for_each(t,callback());
};

int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip(std::string("255.255.255.255"));
    print_ip(std::vector<int>{1,2,3,4});
    print_ip(std::list<int>{5,6,7,8});
    print_ip(std::make_tuple(1, 2, 3,4,5));
    return 0;
}