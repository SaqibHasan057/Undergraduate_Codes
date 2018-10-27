// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
//#include "noff.h"
#include "synch.h"
#include "memorymanager.h"

extern MemoryManager *memoryManager;
extern Lock *memoryLock;
extern int LRUClock;

//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    //NoffHeader noffH;
    unsigned int i, j, size;
//printf("In addresspace!!\n");
    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    //printf("In addresspace!!\n");
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;

    //ASSERT(numPages <= NumPhysPages);		// check we're not trying
						// to run anything too big --
						// at least until we have
						// virtual memory

    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
					numPages, size);
// first, set up the translation 
    pageTable = new TranslationEntry[numPages];
    for (i = 0; i < numPages; i++) {
    	pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
    	pageTable[i].physicalPage = -1;
    	/*
        if(memoryManager->IsAnyPageFree() == true)
            pageTable[i].physicalPage = memoryManager->AllocPage();
        else
        {
            for(j = 0; j < i; ++j)
                memoryManager->FreePage(pageTable[j].physicalPage);
            ASSERT(false);
        }
        */

    	pageTable[i].valid = false;
    	pageTable[i].use = false;
    	pageTable[i].dirty = false;
    	pageTable[i].readOnly = false;  // if the code segment was entirely on 
                    					// a separate page, we could set its 
                    					// pages to be read-only
    }
    
    // zero out the entire address space, to zero the unitialized data segment 
    // and the stack segment
    //bzero(machine->mainMemory, size);
    //memoryLock->Acquire();
   /* for(i = 0; i < numPages; ++i)
    {
        bzero(&machine->mainMemory[pageTable[i].physicalPage * PageSize], PageSize);
    }

    */

    
    // then, copy in the code and data segments into memory
   /* unsigned int numPagesForCode = divRoundUp(noffH.code.size, PageSize);
    DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
		noffH.code.virtualAddr, noffH.code.size);
    for(i = 0; i < numPagesForCode; ++i)
    {
        executable->ReadAt(&(machine->mainMemory[ pageTable[i].physicalPage * PageSize ]),
                            PageSize, 
                            noffH.code.inFileAddr + i * PageSize);
    }

    unsigned int numPagesForData = divRoundUp(noffH.initData.size, PageSize);

    DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
        noffH.initData.virtualAddr, noffH.initData.size);
    for(j = numPagesForCode; j < numPagesForCode + numPagesForData; ++j)
    {
        executable->ReadAt(&(machine->mainMemory[ pageTable[i].physicalPage * PageSize ]),
                            PageSize, 
                            noffH.initData.inFileAddr + (j - numPagesForCode) * PageSize);
    }

    */
    //memoryLock->Release();

    swapSpaceFile = new SwapSpace(numPages,currentThread->id);

}

//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
   delete pageTable;
   delete localExecutable;
   delete swapSpaceFile;
}


void
AddrSpace::loadExecutable(int memoryIndex,int size,int filePointer){
	this->localExecutable->ReadAt(&(machine->mainMemory[memoryIndex]),size, filePointer);
}

void 
AddrSpace::bzeroUnitData(int memoryIndex,int size){
	bzero(&machine->mainMemory[memoryIndex], size);
}



int 
AddrSpace::loadIntoFreePage(int addr){

	//memorock->Acquire();

	int vpn = addr/PageSize;
	TranslationEntry *pte = &machine->pageTable[vpn];
	int physicalPageNo = memoryManager->Alloc(currentThread->id,pte);
	if(physicalPageNo==-1){physicalPageNo=memoryManager->AllocByForce(1,currentThread->id,pte);}
	pte->virtualPage = vpn;
	pte->physicalPage = physicalPageNo;
	pte->valid = true;
	pte->dirty = false;
	pte->use = false;
	pte->readOnly=false;
	pte->LRUCount = LRUClock++;

	printf("BadAddress Vpn PhyscialPage %d %d %d\n",addr,vpn,physicalPageNo);

	if(!swapSpaceFile->isSwapPageExists(pte)){
		int codeStartingAddress = noffH.code.virtualAddr;
		int codeSize = noffH.code.size;
		int codeEndingAddress = codeStartingAddress+codeSize-1;

		int initDataStartingAddress = noffH.initData.virtualAddr;
		int initDataSize = noffH.initData.size;
		int initDataEndingAddress = initDataStartingAddress + initDataSize - 1;

		int unInitDataStartingAddress = initDataEndingAddress + 1;

		int startingAddress = vpn*PageSize;
		int endingAddress = startingAddress + PageSize -1;

		if(startingAddress>=codeStartingAddress && startingAddress<=codeEndingAddress && codeSize>0){

			if(endingAddress<=codeEndingAddress){
				int memoryIndex = physicalPageNo * PageSize;
				int codeLoadingSize = PageSize;
				int filePointer = noffH.code.inFileAddr + (startingAddress-codeStartingAddress);

				loadExecutable(memoryIndex,codeLoadingSize,filePointer);
				printf("Case 1\n");
			}
			else if(endingAddress<=initDataEndingAddress && initDataSize>0){
				int memoryIndex = physicalPageNo * PageSize;
				int codeLoadingSize = codeEndingAddress-startingAddress+1;
				int filePointer  = noffH.code.inFileAddr + (startingAddress-codeStartingAddress);

				loadExecutable(memoryIndex,codeLoadingSize,filePointer);

				memoryIndex = physicalPageNo * PageSize + codeLoadingSize;
				int initDataLoadingSize = PageSize - codeLoadingSize;
				filePointer = noffH.initData.inFileAddr;
				
				loadExecutable(memoryIndex,initDataLoadingSize,filePointer);
				printf("Case 2\n");

			}
			else{
				int memoryIndex = physicalPageNo * PageSize;
				int codeLoadingSize = codeEndingAddress-startingAddress+1;
				int filePointer  = noffH.code.inFileAddr + (startingAddress-codeStartingAddress);

				loadExecutable(memoryIndex,codeLoadingSize,filePointer);

				int initDataLoadingSize = 0;

				if(initDataSize>0){
					memoryIndex = physicalPageNo * PageSize + codeLoadingSize;
				    initDataLoadingSize = initDataSize;
					filePointer = noffH.initData.inFileAddr;
				
					loadExecutable(memoryIndex,initDataLoadingSize,filePointer);	
				}

				memoryIndex = physicalPageNo * PageSize + codeLoadingSize + initDataLoadingSize;
				int unitDataLoadingSize= PageSize-codeLoadingSize-initDataLoadingSize;

				bzeroUnitData(memoryIndex,unitDataLoadingSize);

				printf("Case 3\n");
			}
		}
		else if(startingAddress>=initDataStartingAddress && startingAddress<=initDataEndingAddress && initDataSize>0){
			if(endingAddress<=initDataEndingAddress){
				int memoryIndex = physicalPageNo * PageSize;
				int initDataLoadingSize = PageSize;
				int filePointer = noffH.initData.inFileAddr + (startingAddress-initDataStartingAddress);
				loadExecutable(memoryIndex,initDataLoadingSize,filePointer);
				printf("Case 4\n");
			}
			else{
				int memoryIndex = physicalPageNo*PageSize;
				int initDataLoadingSize = (initDataEndingAddress-startingAddress)+1;
				int fileStart  = noffH.initData.inFileAddr + (startingAddress-initDataStartingAddress);
				
				loadExecutable(memoryIndex,initDataLoadingSize,fileStart);
				
				memoryIndex = physicalPageNo*PageSize + initDataLoadingSize;
				int unitDataLoadingSize = PageSize - initDataLoadingSize;
				
				bzeroUnitData(memoryIndex,unitDataLoadingSize);
				
				printf("Case 5\n");
			}
		}
		else{
			bzeroUnitData(physicalPageNo*PageSize,PageSize);
			printf("Case 6\n");
		}
	}
	else{
		swapSpaceFile->loadFromSwapSpace(pte);
		printf("Brought in from swap space.\n");
	}



	

	//memoryLock->Release();



	
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void AddrSpace::SaveState() 
{}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void AddrSpace::RestoreState() 
{
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
}
