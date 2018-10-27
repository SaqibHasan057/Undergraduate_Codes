#include<string.h>
#include<string>
#ifndef SYMBOLINFO_H_INCLUDED
#define SYMBOLINFO_H_INCLUDED

using namespace std;

class SymbolInfo{

    public:
        char *type;
        char *symbol;
        double value;
        string code;
        int arrayLength;
        int arrIndex;
		string arrIndexHolder;
        SymbolInfo *next;


        SymbolInfo(){
            symbol=NULL;
            type=NULL;
            value=-9999999;
            code="";
			arrIndex=-1;
        }

        SymbolInfo(char *symbol, char *type){
            this->symbol=new char[strlen(symbol)+1];
            this->type= new char[strlen(type)+1];
            strcpy(this->symbol,symbol);
            strcpy(this->type,type);
            this->next=NULL;
			arrIndexHolder="";
            value=-9999999;
            code="";
            arrayLength=0;
            arrIndex=-1;
        }

        SymbolInfo(const SymbolInfo *sym){
         	this->symbol=NULL;
            if(sym->symbol!=NULL){
                this->symbol=new char[strlen(sym->symbol)+1];
                strcpy(this->symbol,sym->symbol);

            }

			this->type=NULL;
			if(sym->type!=NULL){
                this->type= new char[strlen(sym->type)+1];
                strcpy(this->type,sym->type);
            }
			
            this->code=sym->code;
            this->value=sym->value;
            this->next=NULL;
			this->arrayLength=sym->arrayLength;
            this->arrIndex=sym->arrIndex;
            this->arrIndexHolder=sym->arrIndexHolder;
        }

        ~SymbolInfo(){
            delete []symbol;
            delete []type;
        }

        char* getSymbol(){return symbol;}
        char* getType(){return type;}
        double getValue() {return value;}


        void setSymbol(char *s){

            if(symbol!=NULL) delete symbol;
            symbol= new char[strlen(s)+1];
            strcpy(symbol,s);

        }
        void setType(char *s){
            if(type!=NULL) delete type;
            type= new char[strlen(s)+1];
            strcpy(type,s);
        }

        void setValue(double value){
            this->value=value;
        }

        void setArrayLength(int a){
            arrayLength=a;
        }

};

#endif
