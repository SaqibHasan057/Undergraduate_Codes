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

    int hashFunction(char*key){
        int index=0;
        int lengthOfString=strlen(key);
        for(int i=0;i<lengthOfString;i++){
            index+=key[i];
        }
        index=index%size;
        index=6*index*index+13;
        index=index%size;
        return index;
    }


    bool insert(char *Name,char *Type,char* decType,double value){
        SymbolInfo *symbol;
        SymbolInfo* checker = lookUp(Name);
        if(checker!=NULL)return false;
        symbol = new SymbolInfo(Name,Type,decType,value);
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

     bool insert(char *Name,char *Type,char* decType,double value,int length){
        SymbolInfo *symbol;
        SymbolInfo* checker = lookUp(Name);
        if(checker!=NULL)return false;
        symbol = new SymbolInfo(Name,Type,decType,value,length);
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

    SymbolInfo* lookUp(char* key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            return NULL;
        }
        else{
            while(temp!=0){
                    if(strcmp(temp->getName(),key)==0){
                        return temp;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
        return NULL;
    }

    SymbolInfo* get(char* key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            return 0;
        }
        else{
            while(temp!=0){
                    if(strcmp(temp->getName(),key)==0){
                        return temp;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
        return 0;
    }

    void update(char* key,double newValue){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            return;
        }
        else{
            while(temp!=0){
                    if(strcmp(temp->getName(),key)==0){
                        temp->setValue(newValue);
                        return;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
    }

     void update(char* key,double newValue,int pointer){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        int link = 0;
        if(temp == 0){
            return;
        }
        else{
            while(temp!=0){
                    if(strcmp(temp->getName(),key)==0){
                        temp->setArrayValue(newValue,pointer);
                        return;
                    }
                    temp=temp->getNext();
                    link++;
            }
        }
    }

    void print(FILE *file){
        for(int i=0;i<size;i++){
            int xyz = 5;
            SymbolInfo *temp = hashTable[i];
            if(temp!=0){fprintf(file,"%d-> ",i);xyz=55;}
            while(temp!=0){
                if(strcmp(temp->getDecType(),"INT")==0)fprintf(file,"<%s,%s,%d>",temp->getName(),temp->getType(),(int)temp->getValue());

                if(strcmp(temp->getDecType(),"FLOAT")==0)fprintf(file,"<%s,%s,%f>",temp->getName(),temp->getType(),temp->getValue());

                if(strcmp(temp->getDecType(),"CHAR")==0)fprintf(file,"<%s,%s,%c>",temp->getName(),temp->getType(),(char)((int)temp->getValue()));

                if(strcmp(temp->getDecType(),"INT_ARRAY")==0){
                fprintf(file,"<%s,%s,{",temp->getName(),temp->getType());
                for(int i=0;i<temp->getLength();i++){fprintf(file,"%d",(int)temp->getArray()[i]);if(i<temp->getLength()-1)fprintf(file,",");}
                fprintf(file,"}>");
                }

                if(strcmp(temp->getDecType(),"FLOAT_ARRAY")==0){
                fprintf(file,"<%s,%s,{",temp->getName(),temp->getType());
                for(int i=0;i<temp->getLength();i++){fprintf(file,"%f",(double)temp->getArray()[i]);if(i<temp->getLength()-1)fprintf(file,",");}
                fprintf(file,"}>");
                }

                if(strcmp(temp->getDecType(),"CHAR_ARRAY")==0){
                fprintf(file,"<%s,%s,{",temp->getName(),temp->getType());
                for(int i=0;i<temp->getLength();i++){fprintf(file,"%c",(char)((int)temp->getArray()[i]));if(i<temp->getLength()-1)fprintf(file,",");}
                fprintf(file,"}>");
                }

                temp=temp->getNext();
            }
            if(xyz==55)fprintf(file,"\n");
        }
        fprintf(file,"\n");
    }

    void deleteKey(char* key){
        int index = hashFunction(key);
        SymbolInfo *temp = hashTable[index];
        SymbolInfo *prev = hashTable[index];
        int link = 0;
        if(temp == 0){
            cout<<"Not Found For Deletion"<<endl;
            return;
        }
        else if(strcmp(temp->getName(),key)==0){
            hashTable[index]=temp->getNext();
            cout<<"Found at "<<index<<","<<link<<endl;
            delete temp;
            return;
        }
        else{
            while(temp!=0){
                    if(strcmp(temp->getName(),key)==0){
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


