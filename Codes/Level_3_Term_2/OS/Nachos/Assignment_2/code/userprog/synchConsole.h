#ifndef SYNCCON_H
#define SYNCCON_H

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "openfile.h"
#include "addrspace.h"
#include "memory_manager.h"
#include "table.h"
#include "synch.h"
#include "console.h"

extern MemoryManager *memory_manager;
extern Table *processTable;

extern Console *mainConsole;
extern Semaphore *readSemaphore;
extern Semaphore *writeSemaphore;
extern Lock *mainConsoleLock;

int Read(int buffer, int size, OpenFileId id);
void Write(int buffer, int size, OpenFileId id);

#endif