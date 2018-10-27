// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create several threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustrate the inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.
//
// Parts from Copyright (c) 2007-2009 Universidad de Las Palmas de Gran Canaria
//

#include "copyright.h"
#include "system.h"
#include "producer.h"
#include "consumer.h"
#include "list.h"
#include "Abul.h"

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 10 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"name" points to a string with a thread name, just for
//      debugging purposes.
//----------------------------------------------------------------------

#define MAX_SIZE 5
Lock *lock;
Condition *P;
Condition *C;
List<int> *globalBuffer;


void initializeGlobalVariables(){
    lock = new Lock("Main Lock");
    P = new Condition("Producer Condition",lock);
    C = new Condition("Consumer Condition",lock);
    globalBuffer = new List<int>;
}

void createNewProducer(void *nameOfProducer){
    char* threadName = (char*)nameOfProducer;
    Producer *producer = new Producer(threadName,lock,P,C,globalBuffer,MAX_SIZE);
    producer->produce();
}

void createNewConsumer(void *nameOfConsumer){
    char* threadName = (char*)nameOfConsumer;
    Consumer *consumer = new Consumer(threadName,lock,P,C,globalBuffer,MAX_SIZE);
    consumer->consume();
}








void
SimpleThread(void* name)
{
    // Reinterpret arg "name" as a string
    char* threadName = (char*)name;
    
    // If the lines dealing with interrupts are commented,
    // the code will behave incorrectly, because
    // printf execution may cause race conditions.
    for (int num = 0; num < 10; num++) {
        //IntStatus oldLevel = interrupt->SetLevel(IntOff);
    printf("*** thread %s looped %d times fuchkas\n", threadName, num);
    //interrupt->SetLevel(oldLevel);
        //currentThread->Yield();
    }
    //IntStatus oldLevel = interrupt->SetLevel(IntOff);
    printf(">>> Thread %s has finished\n", threadName);
    
    // If the lines dealing with interrupts are commented,
    // the code will behave incorrectly, because
    // printf execution may cause race conditions.
    for (int num = 0; num < 10; num++) {
        //IntStatus oldLevel = interrupt->SetLevel(IntOff);
	printf("*** thread %s looped %d times fuchkas\n", threadName, num);
	//interrupt->SetLevel(oldLevel);
        //currentThread->Yield();
    }
    //IntStatus oldLevel = interrupt->SetLevel(IntOff);
    printf(">>> Thread %s has finished\n", threadName);
    //interrupt->SetLevel(oldLevel);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Set up a ping-pong between several threads, by launching
//	ten threads which call SimpleThread, and finally calling 
//	SimpleThread ourselves.
//----------------------------------------------------------------------

/*void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");

    for ( int k=1; k<=10; k++) {
      char* threadname = new char[100];
      sprintf(threadname, "Hilo %d", k);
      Thread* newThread = new Thread (threadname);
      newThread->Fork (SimpleThread, (void*)threadname);
    }
    
    SimpleThread( (void*)"Hilo 0");
}*/

void
ThreadTest()
{
    DEBUG('t', "Entering SimpleTest");
    initializeGlobalVariables();
    printf("It has started!!\n");
    Abul myAbul;
    printf("This is for testing %s\n\n",myAbul.getAbul());
    

    for ( int k=1; k<=10; k++) {
      char* threadname = new char[100];
      sprintf(threadname, "Producer %d", k);
      printf("%s has been created!!\n\n",threadname );
      Thread* newThread = new Thread (threadname);
      newThread->Fork (createNewProducer, (void*)threadname);
      //printf("Esto\n");
    }

    //printf("OLA\n");
    for ( int k=1; k<=10; k++) {
      char* threadname = new char[100];
      sprintf(threadname, "Consumer %d", k);
      printf("%s has been created!!\n\n",threadname );
      Thread* newThread = new Thread (threadname);
      newThread->Fork (createNewConsumer, (void*)threadname);
      //printf("Estosiosa\n\n");
    }
   
}

