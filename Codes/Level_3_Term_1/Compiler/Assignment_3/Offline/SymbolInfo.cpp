#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include <new>
using namespace std;

class SymbolInfo{
    char Name[100];
    char Type[100];
    char decType[100];
    double value;
    double* arrayPointer;
    int arrayLength;
    SymbolInfo *next;

public:

    SymbolInfo(char* Name,char* Type,char* decType,double value){
        strcpy(this->Name,Name);
        strcpy(this->Type,Type);
        strcpy(this->decType,decType);
        this->value=value;
        next = 0;
    }

    SymbolInfo(char* Name,char* Type,char* decType,double value,int arrayLength){
        strcpy(this->Name,Name);
        strcpy(this->Type,Type);
        strcpy(this->decType,decType);
        this->value=value;
        this->arrayLength=arrayLength;
        arrayPointer=new double[arrayLength];
        for(int i=0;i<arrayLength;i++)arrayPointer[i]=0;
        next = 0;
    }


    void setName(char* Name){strcpy(this->Name,Name);}

    void setType(char* Type){strcpy(this->Type,Type);}

    void setDecType(char* decType){strcpy(this->decType,decType);}

    void setValue(double value){this->value=value;}

    void setLength(int length){this->arrayLength=length;}

    void setArrayValue(double value,int index){arrayPointer[index]=value;}

    void setNext(SymbolInfo* symbol){this->next=symbol;}

    char* getName(){return Name;}

    char* getType(){return Type;}

    char* getDecType(){return decType;}

    double getValue(){return value;}

    int getLength(){return arrayLength;}

    double* getArray(){return arrayPointer;}

    int getIndex(double value){
    for(int i=0;i<arrayLength;i++)if(arrayPointer[i]==value)return i;
    return 0;
    }

    SymbolInfo* getNext(){return next;}

};
