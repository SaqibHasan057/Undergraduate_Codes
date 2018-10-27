#include <bits/stdc++.h>
#define MAX 9999

using namespace std;
int temporary[10000][10000];
int outputAnswer[10000][10000];
int sizeofArray=0;
int numberOfBreakPoints=0;
int result=0;

int *breakingPointArray(int *array,int sizeofArray)
{
    int *returnArray;
    returnArray = new int[sizeofArray];
    numberOfBreakPoints = 0;
    if(array[0]!=1)
    {
            returnArray[numberOfBreakPoints] = 0;
            numberOfBreakPoints++;
    }
    for(int i=1;i<sizeofArray;i++)
    {

    if(array[i-1]-array[i]>1 || array[i] - array[i-1]>1)
        {
            returnArray[numberOfBreakPoints] =  i;
            numberOfBreakPoints++;
        }
    }
    returnArray[numberOfBreakPoints] = sizeofArray;
    numberOfBreakPoints++;

    return returnArray;
}

int numOfBP(int *array,int sizeOfArray)
{
    numberOfBreakPoints = 0;
    if(array[0]!=1)
    {
            numberOfBreakPoints++;
    }
    for(int i=0;i<sizeofArray;i++)
    {

    if(i>0 && (array[i-1]-array[i]>1 || array[i] - array[i-1]>1))
        {
            numberOfBreakPoints++;
        }
    }
    numberOfBreakPoints++;

    return numberOfBreakPoints;
}

void printArray(int *A,int size){
    for(int i=0;i<size;i++) cout<<A[i]<<" ";
    cout<<endl;
}

void copyArray(int *A,int *B,int size){
    for(int i=0;i<size;i++){
        B[i]=A[i];
    }
}

void reverseArray(int *array, int x,int y)
{
    int temp;
    while (x < y)
    {
        temp = array[x];
        array[x] = array[y];
        array[y] = temp;
        x++;
        y--;
    }
}

int mainCode(int array[],int reversals,int pBP)
{
   int storeA[sizeofArray];
   float lowerBound;
   float mini = MAX;
   int r;
   int *breakPoint = breakingPointArray(array,sizeofArray);
   int now = numOfBP(array,sizeofArray);
   if(pBP==now) return MAX;
   int prevBP = now;
   if(now==1){
        if(result>reversals){
            for(int i=0;i<reversals;++i)
                for(int j=0;j<sizeofArray;++j)
                    outputAnswer[i][j]=temporary[i][j];
        result=reversals;
        }
        return reversals;
   }
   else{
   for(int i=0;i<now;i++)
   {
       int j = i;
       while(j<now)
       {
           copyArray(array,storeA,sizeofArray);
           reverseArray(storeA,breakPoint[i],breakPoint[j]-1);
           int numberOfBreakPoints = numOfBP(storeA,sizeofArray);
           lowerBound = reversals + (float)numberOfBreakPoints/2;
           if(lowerBound<=mini)
           {
               mini = lowerBound;

            for(int i=0;i<sizeofArray;++i)
                    temporary[reversals][i]= storeA[i];
            r = mainCode(storeA,reversals+1,prevBP);
            }
            j++;
        }
   }
   }

   return r;
}
int main()
{
    cin>>sizeofArray;

    int array[sizeofArray];
    int temp[sizeofArray];
    for(int i=0;i<sizeofArray;i++)
    {
        int num;
        cin>>num;
        array[i] = num;
    }
    result=sizeofArray;
    mainCode(array,0,MAX);
    cout<<"Number of reversals:"<<result<<endl;
    for(int i=0;i<result;++i){
        for(int j=0;j<sizeofArray;++j)
            cout << outputAnswer[i][j] << " ";
        cout << endl;
    }
}
