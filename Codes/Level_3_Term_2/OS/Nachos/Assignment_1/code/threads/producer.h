#include "list.h"
#include "copyright.h"
#include "synch.h"


class Producer{
public:
	Producer(char *debugName,Lock *lock,Condition *P,Condition *C,List<int> *globalBuffer,int maxSizeOfTheBuffer);
	int createProduct();
	void produce();
private:
	char *nameOfProducer;
	Lock *lock;
	Condition *C;
	Condition *P;
	List<int> *globalBuffer;
	int maxSizeOfTheBuffer;


};