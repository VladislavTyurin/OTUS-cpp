#pragma once

#include "Bulk.h"

class Writer
{
public:
    virtual void Write(Bulk*) = 0;
    virtual ~Writer(){};
};

class ConsoleWriter:public Writer
{
public:
    void Write(Bulk* b) override
    {
        b->ConsoleWrite();
    }
};

class FileWriter:public Writer
{
public:
    void Write(Bulk* b) override
    {
        b->WriteFile();
    }
};
