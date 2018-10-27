#include "queue.c"

int length;
int currentMaxLength;
int *array;


int lengthD;
int arrayD[500][2];



int lengthBannedList;
int bannedList[500];






void initializeDataStructure(){
	length=0;
	currentMaxLength=2;
	array = (int*)malloc(1000*sizeof(int));

	lengthD=0;

	lengthBannedList=0;
	
}

void insertElement(int data){
	array[length]=data;
	length++;
}

int searchElement(int data){
	for(int i=0;i<length;i++){
		if(array[i]==data)return i;
	}
	return -1;
}

int duplicate(int data){
	int count = 0;
	for(int i=0;i<length;i++){
		if(array[i]==data)count++;
	}
	if(count==0)return 0;
	else if (count==1)return -1;
	else return 1;
}

void deleteMultiple(int data){
	for(int i=0;i<length;i++){
		if(array[i]==data){
			array[i]=array[length-1];
			length--;
		}
	}
}


void deleteElement(int data){
	int index = searchElement(data);
	if(index!=-1){
		array[index]=array[length-1];
		length--;
	}
}

void printDataStructure(){
	printf("Data Structure: ");
	for(int i=0;i<length;i++)printf("%d,",array[i]);
	printf("end\n\n");
}


void insertArrayD(int studentId,int bit){
	arrayD[lengthD][0]=studentId;
	arrayD[lengthD][1]=bit;
	lengthD++;
}

int searchArrayD(int data){
	for(int i=0;i<lengthD;i++){
		if(arrayD[i][0]==data)return i;
	}
	return -1;
}

int checkArrayD(int data){
	int x = searchArrayD(data);
	if(x==-1)return 0;
	else{
		if(arrayD[x][1]==-1)return -1;
		else return 1;
	}
}

int deleteArrayD(int data){
	int index = searchArrayD(data);
	if(index!=-1){
		arrayD[index][0]=arrayD[lengthD-1][0];
		arrayD[index][1]=arrayD[lengthD-1][1];
		lengthD--;
	}
}

int printArrayD(){
	printf("ArrayD: ");
	for(int i=0;i<lengthD;i++)printf("%d,",arrayD[i][0]);
	printf("\n\n");
}

int insertBannedList(int data){
	bannedList[lengthBannedList]=data;
	lengthBannedList++;
}

int searchBannedList(int data){
	for(int i=0;i<lengthBannedList;i++){
		if(bannedList[i]==data)return 1;
	}
	return 0;
}




