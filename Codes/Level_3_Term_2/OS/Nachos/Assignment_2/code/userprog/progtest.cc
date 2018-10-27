// progtest.cc 
//	Test routines for demonstrating that Nachos can load
//	a user program and execute it.  
//
//	Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"
#include "memory_manager.h"
#include "table.h"

//----------------------------------------------------------------------
// StartProcess
// 	Run a user program.  Open the executable, load it into
//	memory, and jump to it.
//----------------------------------------------------------------------


MemoryManager *memory_manager;
Table *processTable;
Console *mainConsole;
Semaphore *readSemaphore;
Semaphore *writeSemaphore;
Lock *mainConsoleLock;

static void R1(void* arg) { readSemaphore->V(); }
static void W1(void* arg) { writeSemaphore->V(); }



void
StartProcess(const char *filename)
{
	printf("StartProcess call\n\n");

    OpenFile *executable = fileSystem->Open(filename);
    AddrSpace *space;

	memory_manager = new MemoryManager(NumPhysPages);
    processTable = new Table(100);
    mainConsole = new Console(NULL, NULL, R1, W1, 0);
    readSemaphore = new Semaphore("read_avail", 0);
    writeSemaphore = new Semaphore("write_done", 0);
    mainConsoleLock = new Lock("main_console_lock");

    currentThread->setID(processTable->Alloc(currentThread));

    

    printf("%s\n\n",filename );

    if (executable == NULL) {
	printf("Unable to open file %s\n", filename);
	return;
    }
    

    space = new AddrSpace(executable);    
    currentThread->space = space;

   
    delete executable;			// close file

    space->InitRegisters();		// set the initial register values
    space->RestoreState();		// load page table register
    //printf("%s\n","StartProcess end!!" );

    machine->Run();			// jump to the user progam
    ASSERT(false);			// machine->Run never returns;
					// the address space exits
					// by doing the syscall "exit"
}

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.



//----------------------------------------------------------------------
// ConsoleInterruptHandlers
// 	Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

Console *console;
Semaphore *readAvail;
Semaphore *writeDone;

static void ReadAvail(void* arg) { readAvail->V(); }
static void WriteDone(void* arg) { writeDone->V(); }


//----------------------------------------------------------------------
// ConsoleTest
// 	Test the console by echoing characters typed at the input onto
//	the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void 
ConsoleTest (const char *in, const char *out)
{
    char ch;

    console = new Console(in, out, ReadAvail, WriteDone, 0);
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    
    for (;;) {
	readAvail->P();		// wait for character to arrive
	ch = console->GetChar();
	console->PutChar(ch);	// echo it!
	writeDone->P() ;        // wait for write to finish
	if (ch == 'q') return;  // if q, quit
    }
}
