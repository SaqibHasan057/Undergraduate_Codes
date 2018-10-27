// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "openfile.h"
#include "addrspace.h"
#include "memory_manager.h"
#include "table.h"
#include "synch.h"
#include "console.h"
#include "synchConsole.h"

#define MAX_SIZE 200


extern MemoryManager *memory_manager;
extern Table *processTable;

extern Console *mainConsole;
extern Semaphore *readSemaphore;
extern Semaphore *writeSemaphore;
extern Lock *mainConsoleLock;

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void forkFunc(void* i){
	currentThread->space->RestoreState();
	currentThread->space->InitRegisters();
	machine->Run();
}

SpaceId newExec(int path)
{
	char executionBuffer[MAX_SIZE];
	int index = 0;
	//printf("%s\n", "This is EXEC testing!!");
	int copyPath;

	do{
		int x;
		if(!machine->ReadMem(copyPath,1,&x))return 0;
		executionBuffer[index]=(char)x;
		index++;
		copyPath++;
	}while(executionBuffer[index]);

	OpenFile *fd = fileSystem->Open(executionBuffer);
	if(fd==NULL)return 0;
	//printf("%s\n", "This is another testing!!");

	AddrSpace *S = new AddrSpace(fd);

	Thread *newThread = new Thread("test");

	int id = processTable->Alloc((void*)newThread);
	//printf("processTable id : %d",id);

	newThread->setID(id);
	newThread->space = S;
	newThread->Fork(forkFunc, 0);

	return newThread->getID();

}


void newExit(int status){
	int sizeOfPageTable = machine->pageTableSize;
	int i = 0;

	for(int i=0;i<sizeOfPageTable;i++){
		memory_manager->FreePage(machine->pageTable[i].physicalPage);
		processTable->Release(currentThread->getID());
		//printf("the id is %d\n",currentThread->getID() );
		if(processTable->getNumOfProcess()==0)interrupt->Halt();
		currentThread->Finish();
	}
}


void
ExceptionHandler(ExceptionType which)
{
	IntStatus oldLevel = interrupt->SetLevel(IntOff);

	int t = machine->ReadRegister(2);
	//printf("Register 2 value: %d\n",t );
    if(which==SyscallException){

    	if(t==SC_Exec){
    		//printf("Exec!!\n");
    		int executionRegisterValue = machine->ReadRegister(4);
    		int executionID = newExec(executionRegisterValue);
    		//printf("Exec Complete!!\n");
    		machine->WriteRegister(2,executionID);

    	}
    	else if(t==SC_Exit){
    		int exitStatus = machine->ReadRegister(4);
    		printf("Exit with status: %d\n",exitStatus);
    		newExit(exitStatus);
    	}
    	else if(t==SC_Halt){
    		interrupt->Halt();
    	}
    	else if(t == SC_Read) {
    		int pathOfRead = machine->ReadRegister(4);
    		int sizeOfRead = machine->ReadRegister(5);
    		int idOfRead = machine->ReadRegister(6);
    		int numberOfBytesRead = Read(pathOfRead,sizeOfRead,idOfRead);
    		machine->WriteRegister(2,numberOfBytesRead); 
    		printf("Number of bytes read is %d\n",numberOfBytesRead);
    	}
    	else if(t == SC_Write) {
    		int pathOfWrite = machine->ReadRegister(4);
    		int sizeOfWrite = machine->ReadRegister(5);
    		int idOfWrite = machine->ReadRegister(6);
    		Write(pathOfWrite,sizeOfWrite,idOfWrite);
    		printf("\n");
    	}
	
    }

    int processCounter; 
	processCounter=machine->ReadRegister(PCReg); 
	machine->WriteRegister(PrevPCReg,processCounter); 
	processCounter=machine->ReadRegister(NextPCReg); 
	machine->WriteRegister(PCReg,processCounter); 
	processCounter += 4; 
	machine->WriteRegister(NextPCReg,processCounter); 


    interrupt->SetLevel(oldLevel);


}
