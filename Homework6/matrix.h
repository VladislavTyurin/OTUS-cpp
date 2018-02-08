#pragma once

#include "matrix_element.h"

template <typename T, int N, T default_value>
class Matrix
{
public:
    Matrix()
    {
        tup = new typename generate_tuple_type<int,N>::type();
        container = new MatrixElementContainer<T,N,default_value>;
        ml = new MatrixElement<T,N-1,N,default_value>(container, tup);
    }

    ~Matrix()
    {
        delete ml;
        delete tup;
        delete container;
    }

    int Size()
    {
        return container->Size();
    }

    void Print()
    {
        container->Print();

    }

    MatrixElement<T,N-1,N,default_value>& operator[](int i)
    {
        std::get<0>(*tup) = i;
        return *ml;
    }

private:
    IContainer<T,N,default_value>* container;
    typename generate_tuple_type<int,N>::type* tup;
    MatrixElement<T,N-1,N,default_value>* ml;
};


//Частичная специализация Matrix с печатью фрагмента(только двумерная матрица)
template <typename T, T default_value>
class Matrix<T,2,default_value>
{
public:
    Matrix()
    {
        tup = new typename generate_tuple_type<int,2>::type();
        container = new MatrixElementContainer<T,2,default_value>;
        ml = new MatrixElement<T,1,2,default_value>(container, tup);
    }

    ~Matrix()
    {
        delete ml;
        delete tup;
        delete container;
    }

    int Size()
    {
        return container->Size();
    }

    void Print()
    {
        container->Print();

    }

    void PrintFragment(int x1, int y1, int x2, int y2)
    {
        container->PrintFragment(x1,y1,x2,y2);
    }


    MatrixElement<T,1,2,default_value>& operator[](int i)
    {
        std::get<0>(*tup) = i;
        return *ml;
    }

private:
    IContainer<T,2,default_value>* container;
    typename generate_tuple_type<int,2>::type* tup;
    MatrixElement<T,1,2,default_value>* ml;
};