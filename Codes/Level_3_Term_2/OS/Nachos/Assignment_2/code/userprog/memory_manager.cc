#include "copyright.h"
#include "memory_manager.h"

MemoryManager::MemoryManager(int numPages)
{
	memoryManagerLock = new Lock("Memory_Manager_Lock");
	pageMap = new BitMap(numPages);
}

int MemoryManager::AllocPage()
{
	memoryManagerLock->Acquire();

	int ret = pageMap->Find();

	memoryManagerLock->Release();

	return ret;
}

void MemoryManager::FreePage(int physPageNum)
{
	memoryManagerLock->Acquire();

	pageMap->Clear(physPageNum);

	memoryManagerLock->Release();
}

bool MemoryManager::PageIsAllocated(int physPageNum)
{
	memoryManagerLock->Acquire();

	bool retVal = pageMap->Test(physPageNum);

	memoryManagerLock->Release();

	return retVal;
}