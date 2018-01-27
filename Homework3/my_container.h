#pragma once

#include <iostream>
#include "map_allocator.h"

template <typename T, typename A = std::allocator<T> >
class MyContainer
{
public:

    struct Node
    {
        T data;
        Node* next;
    };

    ~MyContainer()
    {
        free();
    }

    void push_back(const T& data)
    {
        if(n == nullptr)
        {
            n=allocator.allocate(1);
            n->next = nullptr;
            head = n;
            allocator.construct(&(n->data), data);

        }
        else
        {
            (n->next)=allocator.allocate(1);
            n = n->next;
            allocator.construct(&(n->data), data);
            n->next = nullptr;
        }
        ++size;
    }

    // Функция прямого прохода с печатью элементов
    void forward()
    {
        n = head;
        while(n!=nullptr)
        {
            std::cout<<n->data<<std::endl;
            n=n->next;
        }
    }

    class Iterator
    {
    public:
        Iterator(Node* _ptr = nullptr):n_ptr(_ptr){};

        bool operator!=(Iterator& rhs)
        {
            return this->n_ptr!=rhs.n_ptr;
        }

        T& operator*()
        {
            return n_ptr->data;
        }

        Iterator& operator++()
        {
            n_ptr = n_ptr->next;
            return *this;
        }

    private:
        Node* n_ptr;
    };

    Iterator begin()
    {
        return Iterator(head);
    }

    Iterator end()
    {
        return nullptr;
    }

private:

    void free()
    {
        //Удаление с конца, если не предусматривать указатель prev в Node
        while(size!=0)
        {
            n=head;
            for(int i = size-1;i>0;--i)
            {
                n = n->next;
            }
            allocator.destroy(n);
            allocator.deallocate(n,1);
            --size;
        }
    }

    using A1 = typename A::template rebind<Node>::other;
    A1 allocator;
    Node* head = nullptr;
    Node* n = nullptr;
    size_t size = 0;
};
