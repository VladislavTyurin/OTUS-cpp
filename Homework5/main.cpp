#include <iostream>
#include <vector>
#include "shape.h"
#include "document.h"

class GraphEditor
{
public:
    GraphEditor()
    {
        std::cout<<"Editor"<<std::endl;
    }

    ~GraphEditor()
    {
        if(doc!=nullptr)
            delete doc;
    }

    void CreateDocument()
    {
        doc = new Document();
    }

    void OpenDocument(std::string doc_name)
    {
        doc->Open(doc_name);
    }

    void SaveDocument()
    {
        doc->Save();
    }

    void SaveAsDocument(std::string new_name)
    {
        doc->SaveAsDocument(new_name);
    }

    void CreateShape(Shape* shape)
    {
        doc->CreateShape(shape);
    }

    void DeleteShape(Shape* shape)
    {
        doc->DeleteShape(shape);
    }

private:
    Document* doc = nullptr;
};

class Command
{
public:
    virtual void execute() = 0;
    virtual ~Command() = default;
protected:
    Command(GraphEditor* g):editor(g) {};
    GraphEditor* editor;

};

class CreateDocumentCommand: public Command
{
public:
    CreateDocumentCommand(GraphEditor* g):Command(g){};
    void execute() override
    {
        editor->CreateDocument();
    }
};

class OpenDocumentCommand: public Command
{
public:
    OpenDocumentCommand(GraphEditor* g, std::string doc_name):Command(g),m_DocName(doc_name){};
    void execute() override
    {
        editor->OpenDocument(m_DocName);
    }
private:
    std::string m_DocName;
};

class SaveDocumentCommand: public Command
{
public:
    SaveDocumentCommand(GraphEditor* g):Command(g){};
    void execute() override
    {
        editor->SaveDocument();
    }
};

class SaveAsDocumentCommand: public Command
{
public:
    SaveAsDocumentCommand(GraphEditor* g, std::string doc_name):Command(g),m_DocName(doc_name){};
    void execute() override
    {
        editor->SaveAsDocument(m_DocName);
    }
private:
    std::string m_DocName;
};

class CreateShapeCommand: public Command
{
public:
    CreateShapeCommand(GraphEditor* g, Shape* s):Command(g),shape(s){};
    void execute() override
    {
        editor->CreateShape(shape);
    }
private:
    Shape* shape;
};

class DeleteShapeCommand: public Command
{
public:
    DeleteShapeCommand(GraphEditor* g, Shape* s):Command(g),shape(s){};
    void execute() override
    {
        editor->DeleteShape(shape);
    }
private:
    Shape* shape;
};


int main() {
    GraphEditor editor;
    std::vector<Command*> commands;

    Shape* cir = new Circle();
    Shape* rect = new Rectangle();

    commands.push_back(new CreateDocumentCommand(&editor));
    commands.push_back(new OpenDocumentCommand(&editor,"exist_doc"));

    commands.push_back(new CreateShapeCommand(&editor,cir));
    commands.push_back(new CreateShapeCommand(&editor, rect));

    commands.push_back(new DeleteShapeCommand(&editor,cir));
    commands.push_back(new DeleteShapeCommand(&editor, rect));

    commands.push_back(new SaveDocumentCommand(&editor));
    commands.push_back(new SaveAsDocumentCommand(&editor,"new_doc"));

    for(auto&& com: commands)
    {
        com->execute();
    }

    for(auto&& com: commands)
    {
        delete com;
    }

    return 0;
}