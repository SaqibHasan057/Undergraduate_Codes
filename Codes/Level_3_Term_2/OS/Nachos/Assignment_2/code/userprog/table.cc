#include "copyright.h"
#include "table.h"

Table::Table(int size){
	sizeOfTable=size;
	tablePointers = new void*[size];
	for(int i=0;i<sizeOfTable;i++){
		tablePointers[i]=0;
	}
	tableLock = new Lock("Table_Lock");
}

int
Table::Alloc(void *object){
	tableLock->Acquire();

	int ret = -1;

	for(int i=0;i<sizeOfTable;i++){
		if(tablePointers[i]==0){
			tablePointers[i]=object;
			ret = i;
			break;
		}
	}
	//printf("Inserted at %d\n",ret );
	tableLock->Release();

	return ret;
}

void*
Table::Get(int index){
	tableLock->Acquire();
	void* ret = tablePointers[index];
	tableLock->Release();
	return &ret;
}

void
Table::Release(int index){
	tableLock->Acquire();
	tablePointers[index]=0;
	tableLock->Release();
}


int
Table::getNumOfProcess(){
	tableLock->Acquire();
	int sum = 0;

	for(int i=0;i<sizeOfTable;i++){
		if(tablePointers[i]!=0)sum++;
	}

	//printf("The sum is %d\n",sum );

	tableLock->Release();
	return sum;
}