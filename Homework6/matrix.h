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