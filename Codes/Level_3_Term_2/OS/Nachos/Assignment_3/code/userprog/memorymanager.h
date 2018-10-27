#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#ifndef BITMAP_H
#include "bitmap.h"
#endif

#ifndef SYNCH_H
#include "synch.h"
#endif

class MemoryManager{
public:
	MemoryManager(int numPages);
	~MemoryManager();
	int AllocPage();
	int Alloc(int processNo,TranslationEntry *entry);
	int AllocByForce(int choice,int processNo,TranslationEntry *entry);
	void FreePage(int physPageNum);
	bool PageIsAllocated(int physPageNum);
	bool IsAnyPageFree();
	int NumFreePages();
private:
	BitMap *bitMap;
	Lock *lock;
	int *processMap;
	TranslationEntry **entries;
	int numberOfPages;
	int *processIdArray;
};

#endif