#pragma once

#include "container.h"

template <typename T, int N, int M,T default_value>
class MatrixElement{
public:

    MatrixElement() = delete;

    MatrixElement(IContainer<T,M,default_value>* _cont,
                  typename generate_tuple_type<T,M>::type* _tup)
            :cont(_cont),tup(_tup){
        ml = new MatrixElement<T,N-1,M,default_value>(cont,tup);
    };

    MatrixElement<T,N-1,M,default_value>& operator[](int key)
    {
        std::get<M-N>(*tup)=key;
        return *ml;
    }

private:
    typename generate_tuple_type<int,M>::type* tup;
    IContainer<T,M,default_value>* cont = nullptr;
    MatrixElement<T,N-1,M,default_value>* ml;
};

template <typename T,int M, T default_value>
class MatrixElement<T,1,M,default_value>{
public:

    MatrixElement() = delete;

    MatrixElement(IContainer<T,M,default_value>* _cont,
                  typename generate_tuple_type<T,M>::type* _tup)
            :cont(_cont),tup(_tup){};

    bool operator==(const T& rhs)
    {
        return value==rhs;
    }

    T& operator=(const T& val)
    {
        value = val;
        if(val != default_value)
            cont->AddElement(std::make_pair(*tup,value));
        else
            cont->DeleteElement(*tup);
        return value;
    };

    MatrixElement<T,1,M,default_value>& operator[](int key)
    {
        std::get<M-1>(*tup)=key;
        return *this;
    }

    T Value()
    {
        return value;
    }

private:
    T value = default_value;
    typename generate_tuple_type<int,M>::type* tup;
    IContainer<T,M,default_value>* cont = nullptr;
};
