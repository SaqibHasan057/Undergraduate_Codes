#include "translate.h"
#include "filesys.h"
#include "bitmap.h"

#ifndef SWAPSPACE_H
#define SWAPSPACE_H

class SwapSpace{
private:
	OpenFile *swapFile;
	BitMap *translationsStoredMap;
	int numberOfPagesStored;
	int processID;

public:
	SwapSpace(int numberOfPagesStored,int processID);
	bool  isSwapPageExists(TranslationEntry *pageTableEntry);
	void saveIntoSwapSpace(TranslationEntry *pageTableEntry);
    void loadFromSwapSpace(TranslationEntry *pageTableEntry); 
};




#endif
