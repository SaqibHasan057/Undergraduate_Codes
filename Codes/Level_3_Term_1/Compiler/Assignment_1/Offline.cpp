#include <iostream>
#include <cstdlib>
#include <new>
#include <stdio.h>
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

class SymbolTable{
    SymbolInfo **hashTable;
    int size;

public:

    SymbolTable(int size){
        this->size=size;
        hashTable = new SymbolInfo*[size];
        for(int i=0;i<size;i++)hashTable[i]=0;
    }

    int hashFunction(string key){
        int index=0;
        for(int i=0;i<key.length();i++){
            index+=key[i];
        }
        index=index%size;
        index=6*index*index+13;
        index=index%7;
        return index;
    }

    void insert(string Name,string Type){
        SymbolInfo *symbol;
        symbol = new SymbolInfo(Name,Type);
        int index = hashFunction(symbol->getName());
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp==0){
            hashTable[index]=symbol;
        }
        else{
            link=1;
            while(temp->getNext()!=0){
                    temp=temp->getNext();
                    link++;
            }
            temp->setNext(symbol);
        }
        cout<<"Inserted at position "<<index<<","<<link<<endl;
    }

    SymbolInfo* lookUp(string key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            cout<<"Not Found"<<endl;
            return 0;
        }
        else{
            while(temp!=0){
                    if(temp->getName()==key){
                        cout<<"Found at "<<index<<","<<link<<endl;
                        return temp;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
        cout<<"Not Found"<<endl;
    }

    void print(){
        for(int i=0;i<size;i++){
            cout<<i<<"->";
            SymbolInfo *temp = hashTable[i];
            while(temp!=0){
                cout<<"<"<<temp->getName()<<","<<temp->getType()<<"> ";
                temp=temp->getNext();
            }
            cout<<endl;
        }
    }

    void deleteKey(string key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        SymbolInfo *prev = hashTable[index];
        int link = 0;
        if(temp == 0){
            cout<<"Not Found For Deletion"<<endl;
            return;
        }
        else if(temp->getName()==key){
            hashTable[index]=temp->getNext();
            cout<<"Found at "<<index<<","<<link<<endl;
            delete temp;
            return;
        }
        else{
            while(temp!=0){
                    if(temp->getName()==key){
                        prev->setNext(temp->getNext());
                        cout<<"Found at "<<index<<","<<link<<endl;
                        delete temp;
                        return;
                    }
                    prev=temp;
                    temp=temp->getNext();
                    link++;
            }
        }
        cout<<"Not Found For Deletion"<<endl;

    }





};



int main(){

    FILE *fpin = freopen("input.txt","r",stdin);
    FILE *fpout = freopen("output.txt","w",stdout);
    int size_of_table;
    cin>>size_of_table;
    SymbolTable table(size_of_table);

    char c;

    while(cin>>c){
        if(c=='P'){
            cout<<c<<endl;
            table.print();
        }
        else if(c=='I'){
            string name,type;
            cin>>name>>type;
            cout<<c<<" "<<name<<" "<<type<<endl;
            table.insert(name,type);
        }
        else if(c=='L'){
            string key;
            cin>>key;
            cout<<c<<" "<<key<<endl;
            table.lookUp(key);
        }
        else if(c=='D'){
            string key;
            cin>>key;
            cout<<c<<" "<<key<<endl;
            table.deleteKey(key);
        }
        cout<<endl;
    }
    return 0;
}
