#include <iostream>
#include <utility>
#include <tuple>
#include <bitset>
#include <vector>
#include <list>
#include <functional>
#include "check_type.h"
#include "print_tuple.h"


/*!
Печатает элементы ip адреса
\param[in] T&& Объект, который нужно распечатать
\param[in] index Число, указывающее, стоит ли этот элемент в начале адреса или нет
*/

struct t_printer
{
    template <typename T>
    void operator()(T&& t, int index)
    {
        if(index==0)
        {
            std::cout<<t;
            return;
        }
        std::cout<<"."<<t;
    }
};

/*!
Обработка целочисленных типов
 */
template <typename T, typename std::enable_if<std::is_integral<T>::value, T*>::type = nullptr>
void print_ip(T&& t)
{
    static t_printer tp;
    auto p = std::bitset<8*sizeof(t)>(t).to_string();
    for(int i=0;i<sizeof(t);++i)
    {
        tp(std::bitset<8>(p,i*8,8).to_ulong(),i);
    }
    std::cout<<std::endl;
}

/*!
Обработка контейнерных типов
\param[in] T&& Объект, который нужно обработать
\param[in] char  - контейнерный тип
 */
template <typename T,typename std::enable_if<is_container<T>::value && !std::is_same<T,std::string>::value,T*>::type = nullptr>
void print_ip(T&& t)
{
    static t_printer tp;
    auto start = t.cbegin();
    auto end = t.cend();
    int i=0;
    for(auto&& el:t)
    {
        tp(el,i++);
    }
    std::cout<<std::endl;
}

/*!
Обработка строк
 */
template <typename T,typename std::enable_if<std::is_same<T,std::string>::value,T*>::type = nullptr>
void print_ip(T&& t)
{
    std::cout<<t<<std::endl;
}

/*!
Отдельная специализация для кортежа
 */
template <typename... Args>
void print_ip(std::tuple<Args...> t)
{
    //Рекурсия: прямой проход - проверка типов
    //обратный проход - печать элементов
    print_tuple(t,t_printer());
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