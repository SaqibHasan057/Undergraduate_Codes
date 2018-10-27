#include <iostream>
using namespace std;


class Node{
    int data;
    int weight;
    Node *next;

public:

    Node(int data,int weight){
        this->data=data;
        this->weight=weight;
        next = 0;
    }

    void setData(int data,int weight){
        this->data = data;
    }

    void setNext(Node *next){
        this->next = next;
    }

    void setWeight(int weight){
        this->weight=weight;
    }

    int getData(){return data;}

    Node* getNext(){return next;}

;    int getWeight(){return weight;}


};

class linkedList{
    int lengthOfList;
    Node *tail;
    Node *head;

public:
    linkedList(){
        head=0;
        tail=0;
        lengthOfList=0;
    }

    int getLength(){return lengthOfList;}

    void addNode(int data,int weight){
        Node *newNode;
        newNode= new Node(data,weight);

        if(head==0 && tail==0){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->setNext(newNode);
            tail=newNode;
        }
        lengthOfList++;
    }

    void deleteNode(int data){
        Node *temp,*prev;
        temp = head;
        if(temp==0)return;
        while(temp!=0){
            if(temp->getData()==data)break;
            prev=temp;
            temp=temp->getNext();
        }
        if(temp==0)return;
        if(head==tail){
            head=0;
            tail=0;
            delete temp;
        }
        else{
            prev->setNext(temp->getNext());
            delete temp;
        }
        lengthOfList--;
    }

    Node *getIterator(){return head;}

    void printList(){
        cout<<"Start-> ";
        Node *temp;
        temp=head;
        for(int i=0;i<lengthOfList;i++){
            cout<<temp->getData()<<"-> ";
            temp=temp->getNext();
        }
        cout<<"End"<<endl;
    }

};




