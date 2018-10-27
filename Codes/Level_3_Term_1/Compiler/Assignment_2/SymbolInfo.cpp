#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <new>
using namespace std;

class SymbolInfo{
    string Name;
    string Type;
    SymbolInfo *next;
public:

    SymbolInfo(string Name,string Type){
        this->Name = Name;
        this->Type = Type;
        next = 0;
    }

    void setName(string Name){this->Name=Name;}

    void setType(string Type){this->Type=Type;}

    void setNext(SymbolInfo* symbol){this->next=symbol;}

    string getName(){return Name;}

    string getType(){return Type;}

    SymbolInfo* getNext(){return next;}

};
