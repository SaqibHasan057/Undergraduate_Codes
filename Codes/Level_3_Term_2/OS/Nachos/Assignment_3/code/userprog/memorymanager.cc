#include "memorymanager.h"
#include "copyright.h"
#include "stdlib.h"
#include "processtable.h"
#define MAX 9999999;
extern ProcessTable *processTable;


MemoryManager::MemoryManager(int numPages)
{
	numberOfPages=numPages;
	bitMap = new BitMap(numPages);
	lock = new Lock("lock of memory manager");
	processMap = new int[numPages];
	processIdArray = new int[numPages];
	entries = new TranslationEntry*[numPages];

	for(int i=0;i<numPages;i++){
		processMap[i]=0;
		entries[i]=0;
	}
}

MemoryManager::~MemoryManager()
{
	delete bitMap;
	delete lock;
}

int
MemoryManager::AllocPage()
{
	lock->Acquire();
	int ret = bitMap->Find();
	lock->Release();
	return ret;
}

void
MemoryManager::FreePage(int physPageNum)
{
	lock->Acquire();
	bitMap->Clear(physPageNum);
	entries[physPageNum]=0;
	lock->Release();
}

bool
MemoryManager::PageIsAllocated(int physPageNum)
{
	lock->Acquire();
	bool ret = bitMap->Test(physPageNum);
	lock->Release();
	return ret;
}

bool
MemoryManager::IsAnyPageFree()
{
	lock->Acquire();
	bool ret;
	if(bitMap->NumClear() == 0)
		ret = false;
	else
		ret = true;
	lock->Release();
	return ret;
}

int
MemoryManager::NumFreePages()
{
	lock->Acquire();
	int ret = bitMap->NumClear();
	lock->Release();
	return ret;
}

int 
MemoryManager::Alloc(int processNo,TranslationEntry *entry)
{
	lock->Acquire();

	for(int i=0;i<numberOfPages;i++){
		if(entries[i]==0){
			entries[i]=entry;
			processIdArray[i]=processNo;
			lock->Release();
			return i;
		}
	}
	printf("Failed to allocate!!\n");
	return -1;
	
}

int
MemoryManager::AllocByForce(int choice,int processNo,TranslationEntry *entry)
{
	int minimumCount = MAX;
	int idForReplacement;

	if(choice==1){
		
		for(int i=0;i<numberOfPages;i++)
		{
			if(entries[i]->LRUCount < minimumCount )
			{
				minimumCount = entries[i]->LRUCount;
				idForReplacement = i;
			}
		}
		printf("Replacing id %d with minimum count %d\n",idForReplacement,minimumCount);
	}
	else{
		idForReplacement=rand()%numberOfPages;
		printf("Replacing random id %d\n",idForReplacement);
	}

	

	int replace  = idForReplacement;

	Thread *t = (Thread*)processTable->Get(processIdArray[replace]);

	if(t){
		t->space->swapSpaceFile->saveIntoSwapSpace(entries[replace]);
		printf("Saving Thread with id %d into swap space.\n",t->id);
	}
	entries[replace]=entry;
	processIdArray[replace]=processNo;
	lock->Release();
	return replace;

}