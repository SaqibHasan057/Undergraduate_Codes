#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "copyright.h"
#include "system.h"
#include "utility.h"
#include "bitmap.h"
#include "synch.h"

class MemoryManager{
private:
	Lock *memoryManagerLock;
	BitMap *pageMap;

public: 
	MemoryManager(int numPages);
	int AllocPage();
	void FreePage(int physPageNum);
	bool PageIsAllocated(int physPageNum);
};

#endif

