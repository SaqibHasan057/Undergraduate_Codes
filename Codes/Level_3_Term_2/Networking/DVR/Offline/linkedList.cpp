#include <iostream>
#include <string.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <sstream>

using namespace std;

#define INFINITY 9999999

class routingHashTable;
class linkedListNode;
class linkedList;

class linkedListNode{
	char ipAdress[100];
	char nextHop[100];
	int cost;
	linkedListNode *next;

public:

	linkedListNode(char *ipAdress,char* nextHop,int cost){
		strcpy(this->ipAdress,ipAdress);
		strcpy(this->nextHop,nextHop);
		this->cost=cost;
		this->next=0;
	}

	void setIpAddress(char *ipAdress){strcpy(this->ipAdress,ipAdress);}
	void setNextHop(char *nextHop){strcpy(this->nextHop,nextHop);}
	void setCost(int cost){this->cost = cost;}
	void setNext(linkedListNode *next){this->next = next;}

	char *getIpAdress(){return ipAdress;}
	char *getNextHop(){return nextHop;}
	int getCost(){return cost;}
	linkedListNode *getNext(){return next;}

	string getStringFormat(){
		string number1(this->ipAdress);
		string number2(this->nextHop);
		string number3 = std::to_string(this->cost);
		string final = number1+" "+number2+" "+number3+"\n";
		return final;
	}
};


class linkedList{
	linkedListNode *head;
	int length;

public:

	linkedList(){
		head=0;
		length=0;
	}

	void insertElement(char *ipAdress,char *nextHop,int cost){
		linkedListNode *newTemp = new linkedListNode(ipAdress,nextHop,cost);

		if(head==0){
			head=newTemp;
		}
		else{
			newTemp->setNext(head);
			head=newTemp;
		}
		this->length++;
	}

	int deleteElement(char *ipAdress){
		linkedListNode *temp,*prev;;
		temp = head;
		prev = head;

		if(temp==0)return -1;

		while(temp!=0){
			if(!strcmp(temp->getIpAdress(),ipAdress))break;
			prev=temp;
			temp=temp->getNext();
		}

		if(temp==0)return -1;

		if(temp==head){
			head=temp->getNext();
			delete(temp);
		}
		else{
			prev->setNext(temp->getNext());
		}
		this->length--;

	}

	linkedListNode *getNode(char *ipAdress){
		linkedListNode *temp;
		temp = head;

		if(temp==0)return 0;

		while(temp!=0){
			if(!strcmp(temp->getIpAdress(),ipAdress))return temp;
			temp=temp->getNext();
		}

		return 0;
	}

	bool contains(char *ipAdress){
		linkedListNode *get = getNode(ipAdress);
		if(get==0)return false;
		else return true;
	}

	void printLinkedList(){
		linkedListNode *temp;
		temp = head;

		while(temp!=0){
			cout<<temp->getIpAdress()<<"          "<<temp->getNextHop()<<"      "<<temp->getCost()<<endl<<endl;
			temp=temp->getNext();
		}

	}

	void changeValueAsHop(char *ipAdressAsHop,int newCost){
		linkedListNode *temp;
		temp=head;

		while(temp!=0){
			if(!strcmp(temp->getNextHop(),ipAdressAsHop)){
				temp->setCost(newCost);
				temp->setNextHop("    -    ");
			}
			temp=temp->getNext();
		}

	}

	void updateValueAsHop(char *ipAdressAsHop,int newCost){
		linkedListNode *temp;
		temp=head;

		while(temp!=0){
			if(!strcmp(temp->getNextHop(),ipAdressAsHop)){
				temp->setCost(temp->getCost()+ newCost);
			}
			temp=temp->getNext();
		}

	}

	void correctInfinityValues(linkedList edgelist,char *ipAdressDown){
		linkedListNode *temp;
		temp=head;
		while(temp!=0){
			if(edgelist.contains(temp->getIpAdress()) && temp->getCost()==INFINITY && strcmp(ipAdressDown,temp->getIpAdress())){
				linkedListNode *node = edgelist.getNode(temp->getIpAdress());
				temp->setCost(node->getCost());
				temp->setNextHop(node->getNextHop());
			}
			temp=temp->getNext();
		}
	}

	string getStringFormat(){
		linkedListNode *temp;
		temp=head;
		string final="";

		while(temp!=0){
			final+=temp->getStringFormat();
			temp=temp->getNext();
		}
		return final;
	}

	bool emptyList(){
		if(head==0 || this->length==0)return true;
		else return false;
	}

	linkedListNode *getHead(){
		return this->head;
	}
};






/*int main(){
	linkedList list;
	list.insertElement("A","b",10);
	list.insertElement("B","c",20);
	list.insertElement("C","c",30);
	list.deleteElement("A");
	list.deleteElement("B");
	list.deleteElement("C");
	list.deleteElement("D");
	list.insertElement("D","d",50);
	list.printLinkedList();
	return 0;
}*/