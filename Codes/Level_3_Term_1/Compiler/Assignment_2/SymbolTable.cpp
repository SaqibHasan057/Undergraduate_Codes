#include "SymbolInfo.cpp"
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
        index=index%size;
        return index;
    }


    bool insert(char const* Name,char const* Type){
        SymbolInfo *symbol;
        string name(Name);
        string type(Type);
        bool checker = lookUp(name);
        if(checker==true)return false;
        symbol = new SymbolInfo(name,type);
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
        return true;
    }

    bool lookUp(string key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            return false;
        }
        else{
            while(temp!=0){
                    if(temp->getName()==key){
                        return true;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
        return false;
    }

    void print(FILE *file){
        for(int i=0;i<size;i++){
            int xyz = 5;
            SymbolInfo *temp = hashTable[i];
            if(temp!=0){fprintf(file,"%d-> ",i);xyz=55;}
            while(temp!=0){
                fprintf(file,"<%s,%s>,",temp->getName().c_str(),temp->getType().c_str());
                temp=temp->getNext();
            }
            if(xyz==55)fprintf(file,"\n");
        }
        fprintf(file,"\n");
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


