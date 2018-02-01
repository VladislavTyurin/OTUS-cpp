#pragma once

#include <iostream>

class Shape
{
public:
    virtual ~Shape() = default;
    virtual Shape& Create() = 0;
    virtual void Delete() = 0;

protected:
    Shape() = default;
};

class Circle: public Shape
{
public:
    Circle& Create() override
    {
        std::cout<<"Create Circle"<<std::endl;
        return *this;
    };

    void Delete() override
    {
        std::cout<<"Delete Circle"<<std::endl;
    }
};

class Rectangle: public Shape
{
public:
    Rectangle& Create() override
    {
        std::cout<<"Create Rectangle"<<std::endl;
        return *this;
    };

    void Delete() override
    {
        std::cout<<"Delete Rectangle"<<std::endl;
    }
};
