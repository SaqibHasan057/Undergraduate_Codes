#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int passwordQueue;
int passwordSend;

int registrationQueue;

int *queueApply;
int lengthOfApplyQueue;



void initializeQueue(){
	queueApply = (int*)malloc(100*(sizeof(int)));
	for(int i=0;i<100;i++)queueApply[i]=0;
	lengthOfApplyQueue=0;

    
}


void enqueueApplication(int input){
	if(lengthOfApplyQueue<100){
		queueApply[lengthOfApplyQueue]=input;
		lengthOfApplyQueue++;
	}
	else{
		printf("The queue is full\n");
	}
}

int dequeueApplication(){
	if(lengthOfApplyQueue>=0){
		int x = queueApply[0];
		for(int i=1;i<lengthOfApplyQueue;i++){
			queueApply[i-1]=queueApply[i];
		}
		queueApply[lengthOfApplyQueue-1]=0;
		lengthOfApplyQueue--;
		return x;
	}
	else{
		printf("The queue is empty\n");
		return -1;
	}
}


void printQueue(int *queueName,int queueCount){
	printf("Queue:\n");
	for(int i=0;i<queueCount;i++){
		printf("%d->",queueName[i]);
	}
	printf("end\n");
}



