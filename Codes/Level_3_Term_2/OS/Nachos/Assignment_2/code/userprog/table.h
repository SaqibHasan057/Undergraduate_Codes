#ifndef TABLE_H
#define TABLE_H

#include "copyright.h"
#include "system.h"
#include "utility.h"
#include "bitmap.h"
#include "synch.h"

class Table{
private:
	void **tablePointers;
	int sizeOfTable;
	Lock *tableLock;
public:
	Table(int size);
	int Alloc(void *object);
	void *Get(int index);
	void Release(int index);
	int getNumOfProcess();

};

#endif