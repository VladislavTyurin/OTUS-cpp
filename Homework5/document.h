#pragma once
#include "shape.h"

#include <iostream>

class Document
{
public:
    Document()
    {
        std::cout << "Create Document" << std::endl;
    }

    void Open(std::string name)
    {
        std::cout<<"Open Document "<<name<<std::endl;
    }

    void Save()
    {
        std::cout<<"Save Document"<<std::endl;
    }

    void SaveAsDocument(std::string new_name)
    {
        std::cout<<"SaveAs Document "<<new_name<<std::endl;
    }

    void CreateShape(Shape* shape)
    {
        shape->Create();
    }

    void DeleteShape(Shape* shape)
    {
        shape->Delete();
        delete shape;
    }

private:
    std::string m_Name;
};
