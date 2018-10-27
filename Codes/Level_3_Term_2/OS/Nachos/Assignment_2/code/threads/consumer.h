#include "list.h"
#include "copyright.h"
#include "synch.h"
class Consumer{
public:
	Consumer(char *debugName,Lock *lock,Condition *P, Condition *C,List<int> *globalBuffer,int maxSizeOfBuffer);
	void consume();
private:
	char *nameOfConsumer;
	Lock *lock;
	Condition *P;
	Condition *C;
	List<int> *globalBuffer;
	int maxSizeOfBuffer;


};