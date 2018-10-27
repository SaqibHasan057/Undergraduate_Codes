#include<stdio.h>
#include<stdlib.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;


void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int getlength()
{
    return length;
}

int insertItemAt(int pos, int item)
{
    if(pos>=length)return NULL_VALUE;
    if (length == listMaxSize)
	{
	    int *tempList;
        int i;
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ;
        }
        free(list) ;
        list = tempList ;
	};
	list[length]=list[pos];
	list[pos]=item;
	length++;
	return SUCCESS_VALUE;
}

int shrink()
{
    if(listMaxSize==LIST_INIT_SIZE)return NULL_VALUE;
    if(length==(listMaxSize/2))
    {
        int *tempList;
        int i;
        listMaxSize=listMaxSize/2;
        tempList=(int*)malloc(sizeof(int)*listMaxSize);
        for(i=0;i<listMaxSize;i++)
        {
            tempList[i]=list[i];
        }
        free(list);
        list=tempList;
    }
    return SUCCESS_VALUE;
}

int deleteLast()
{
    if(length>0)length--;
    shrink();
}

int clear()
{
    length=0;
    listMaxSize=NULL_VALUE;
    free(list);
    return SUCCESS_VALUE;
}

int deleteAll()
{
    int i;
    length=0;
    if(listMaxSize>LIST_INIT_SIZE)
    {
        listMaxSize=LIST_INIT_SIZE;
        list=(int*)malloc(sizeof(int)*listMaxSize);
    }
    return SUCCESS_VALUE;
}

int insertSorted(int item)
{
    int pos=0;
    for(pos=0;pos<length;pos++)
    {
        if(list[pos]==item)return NULL_VALUE;
    }
    if(length==listMaxSize)
    {
        listMaxSize=listMaxSize*2;
        int *temp;
        temp=(int*)malloc(sizeof(int)*listMaxSize);
        for(int i=0;i<length;i++)
        {
            temp[i]=list[i];
        }
        free(list);
        list=temp;
    }

    pos=length-1;
    while(list[pos]>item && pos>=0)
    {
        list[pos+1]=list[pos];
        pos--;
    }
    if(pos==-1)list[0]=item;
    else list[pos+1]=item;
    length++;
    return SUCCESS_VALUE;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	int * tempList ;

	if(listMaxSize==NULL_VALUE)initializeList();

	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
	shrink();
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	deleteItemAt(position) ;
	shrink();
	return SUCCESS_VALUE ;
}

void printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item at. 3. Delete item.\n");
        printf("4. Get length 5. Insert item at position 6. Delete last item.\n");
        printf("7. Clear list. 8. Delete all in list. 9. Print. \n");
        printf("10. Insert item in a sorted list. 11. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int pos;
            scanf("%d", &pos);
            deleteItemAt(pos);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch==4)
        {
            int listsize;
            listsize=getlength();
            printf("%d\n",listsize);
        }
        else if(ch==5)
        {
            int item,pos;
            printf("Enter item:");
            scanf("%d",&item);
            printf("Enter position:");
            scanf("%d",&pos);
            insertItemAt(pos,item);
        }
        else if(ch==6)
        {
            deleteLast();
        }
        else if(ch==7)
        {
            clear();
        }
        else if(ch==8)
        {
            deleteAll();
        }
        else if(ch==9)
        {
            printList();
        }
        else if(ch==10)
        {
            int sort;
            printf("Enter item:");
            scanf("%d",&sort);
            insertSorted(sort);
        }
        else if(ch==11)
        {
            break;
        }
    }

}

/*int main()
{
    initializeList();
    int i,j,k;
    int c;
    char sr[100];
    i=0;
    k=0;

    printf("Enter string:");
    scanf("%s",&sr);

    while(sr[i]!='\0')
    {
        if(sr[i]=='(' || sr[i]=='{' || sr[i]=='[')
        {
            insertItem(sr[i]);
        }
        else
        {
            if(length==0)
            {
                k=1;
                break;
            }
            c=list[length-1];
            deleteLast();
            if(sr[i]==')' && c!='(')
            {
                k=1;
                break;
            }
            else if(sr[i]=='}' && c!='{')
            {
                k=1;
                break;
            }
            else if(sr[i]==']' && c!='[')
            {
                k=1;
                break;
            }
        }
        i++;
    }
    j=getlength();
    if(!j && !k)printf("Balanced");
    else printf("Not Balanced");
    clear();
}*/
