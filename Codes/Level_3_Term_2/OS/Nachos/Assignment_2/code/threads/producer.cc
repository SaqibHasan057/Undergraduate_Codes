#include "producer.h"
#include "copyright.h"
#include "synch.h"
#include <iostream>
#include <stdlib.h>
using namespace std;


Producer::Producer(char *debugName,Lock *lock,Condition *P,Condition *C,List<int> *globalBuffer,int maxSizeOfTheBuffer){
	this->nameOfProducer = debugName;
	this->lock = lock;
	this->C = C;
	this->P = P;
	this->globalBuffer = globalBuffer;
	this->maxSizeOfTheBuffer = maxSizeOfTheBuffer;
}

int Producer::createProduct(){
	return (rand()*2+5)%30;
}

void Producer::produce(){
	while(1){
		int product = createProduct();
		cout<<nameOfProducer<<" created the product "<<product<<"\n\n";
		lock->Acquire();
		cout<<nameOfProducer<<" has acquired the lock."<<"\n\n";
		if(globalBuffer->getSize()==maxSizeOfTheBuffer){
			P->Wait();
			cout<<nameOfProducer<<" is waiting for buffer to clear."<<"\n\n";
		}
		else {
			for(int i=0;i<300000000;i++);
			globalBuffer->Append(product);
			cout<<nameOfProducer<<" has put the product "<<product<<" into the buffer."<<"\n\n";
			for(int i=0;i<300000000;i++);
		}
	    cout<<nameOfProducer<<" is releasing the lock."<<"\n\n";
		lock->Release();
		C->Broadcast();
	}
}