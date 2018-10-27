#include "copyright.h"
#include "synchConsole.h"


int Read(int buffer, int size, OpenFileId id)
{
	//printf("Read called\n");
	mainConsoleLock->Acquire();
	int numberOfBytes = 0;
	int count=0;
	while(count<size){
		readSemaphore->P();
		char ch = mainConsole->GetChar();

		if(ch!='\n'){
			machine->WriteMem(buffer+count,1,ch);
			numberOfBytes++;
		}
		else break;
		
		count++;
	}
	mainConsoleLock->Release();
	return numberOfBytes;
}


void Write(int buffer, int size, OpenFileId id)
{
	//printf("Write called\n");
	mainConsoleLock->Acquire();
	int count = 0 ;
	
	while(count<size){
		int readValue;
		machine->ReadMem(buffer+count,1,&readValue);
		char character = (char)readValue;
		mainConsole->PutChar(character);
		writeSemaphore->P();
		count++;
	}
	printf("\nThe number of bytes written is %d\n",count);
	mainConsoleLock->Release();
}