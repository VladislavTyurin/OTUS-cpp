#pragma once

#include <iostream>

template<typename T, uint num_elems>
class map_allocator {
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const pointer;
    using reference = T&;
    using const_reference = const reference;
    template<typename U>
    struct rebind
    {
        using other =  map_allocator<U,num_elems>;
    };

    map_allocator()
    {
        pool = malloc(num_elems*sizeof(T));
        Head = reinterpret_cast<T*>(pool);
        Tail = Head+(num_elems);
    }

    ~map_allocator()
    {
        Head = nullptr;
        Tail = nullptr;
        std::free(pool);
    }

    T* allocate(size_t n)
    {
        if(Head<Tail)
        {
            if(!Head)
                throw std::bad_alloc();
            return Head++;
        }
        else
        {
            std::free(pool);
            Head=nullptr;
            Tail=nullptr;
            throw std::bad_alloc();
        }
    }

    void deallocate(T* p, size_t n)
    {

    }

    template<typename U,typename... Args>
    void construct(U* p, Args&&... args)
    {
        new((void*)p) U(std::forward<Args...>(args...));
    }

    template<typename U>
    void destroy(U* p)
    {
        p->~U();
    }

private:
    void* pool = nullptr;
    T* Head = nullptr;
    T* Tail = nullptr; //Участок памяти, следующий за последним элементом
};

