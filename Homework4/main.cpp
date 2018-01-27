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
struct printer
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
//template <typename T>
//void printer(T&& t, int index)
//{
//    if(index==0)
//    {
//        std::cout<<t;
//        return;
//    }
//    std::cout<<"."<<t;
//}

/*!
Обработка целочисленных типов
\param[in] T&& Объект, который нужно обработать
\param[in] int  - целочисленный тип
 */

template <typename T, typename Printer>
void print(T&& t, Printer printer, int)
{
    auto p = std::bitset<8*sizeof(t)>(t).to_string();
    for(int i=0;i<sizeof(t);++i)
    {
        printer(std::bitset<8>(p,i*8,8).to_ulong(),i);
    }
    std::cout<<std::endl;
}

/*!
Обработка контейнерных типов
\param[in] T&& Объект, который нужно обработать
\param[in] char  - контейнерный тип
 */
template <typename T, typename Printer>
void print(T&& t, Printer printer, char)
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

/*!
Обработка строк
\param[in] std::string строка, которую нужно обработать
\param[in] int  - char  - контейнерный тип
 */
template <typename Printer>
void print(std::string t, Printer, char)
{
    std::cout<<t<<std::endl;
}

/*!
Отделяет контейнеры от целочисленных типов
\param[in] T&& Объект, который нужно обработать
 */
template <typename T>
void print_ip(T&& t)
{
    print(t,printer(),is_container<T>::value);
}

/*!
Отдельная специализация для кортежа
 */
template <typename... Args>
void print_ip(std::tuple<Args...> t)
{
    //Рекурсия: прямой проход - проверка типов
    //обратный проход - печать элементов
    print_tuple(t,printer());
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