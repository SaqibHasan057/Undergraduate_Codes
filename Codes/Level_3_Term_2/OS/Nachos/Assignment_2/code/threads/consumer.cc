#include "consumer.h"
#include "copyright.h"
#include "synch.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

Consumer::Consumer(char *debugName,Lock *lock,Condition *P, Condition *C,List<int> *globalBuffer,int maxSizeOfBuffer){
	this->nameOfConsumer = debugName;
	this->lock = lock;
	this->P = P;
	this->C = C;
	this->globalBuffer = globalBuffer;
	this->maxSizeOfBuffer = maxSizeOfBuffer;
}





void Consumer::consume(){
	while(1){
		lock->Acquire();
		cout<<nameOfConsumer<<" has acquired the lock."<<"\n\n";
		if(globalBuffer->getSize()==0){
			C->Wait();
			cout<<nameOfConsumer<<" is waiting."<<"\n\n";
		}
		else{
			for(int i=0;i<300000000;i++);
			int cosumption=globalBuffer->Remove();
			cout<<nameOfConsumer<<" has removed and is now consuming "<<cosumption<<"\n\n";
			for(int i=0;i<300000000;i++);
		}
	    cout<<nameOfConsumer<<" is releasing the lock."<<"\n\n";
		lock->Release();
		P->Broadcast();
	}
}