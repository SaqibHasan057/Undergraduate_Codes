#include "system.h"
#include "swapSpace.h"


SwapSpace::SwapSpace(int numberOfPagesStored,int processID){


	this->numberOfPagesStored=numberOfPagesStored;
	this->processID=processID;
	this->translationsStoredMap = new BitMap(numberOfPagesStored);


	char swapSpaceFileName[100];
	sprintf(swapSpaceFileName,"SwapSpaceMemory:%d",processID);
	
	fileSystem->Create(swapSpaceFileName,numberOfPagesStored*PageSize);

	swapFile = fileSystem->Open(swapSpaceFileName);

}

bool
SwapSpace::isSwapPageExists(TranslationEntry *pageTableEntry){
	if(translationsStoredMap->Test(pageTableEntry->virtualPage))return true;
	else return false;
}


void
SwapSpace::loadFromSwapSpace(TranslationEntry *pageTableEntry){
	swapFile->ReadAt(&(machine->mainMemory[pageTableEntry->physicalPage * PageSize]),PageSize,pageTableEntry->virtualPage*PageSize);
}


void
SwapSpace::saveIntoSwapSpace(TranslationEntry *pageTableEntry){
	pageTableEntry->valid = false;

	if(!isSwapPageExists(pageTableEntry) || pageTableEntry->dirty){
		swapFile->WriteAt(&(machine->mainMemory[pageTableEntry->physicalPage*PageSize]), PageSize,pageTableEntry->virtualPage*PageSize);
		translationsStoredMap->Mark(pageTableEntry->virtualPage);
	}

}




