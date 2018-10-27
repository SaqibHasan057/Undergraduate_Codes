#include <iostream>
using namespace std;
#define NULL_VALUE -1

void swap(int *A,int x,int y){
    int t;
    t=A[x];
    A[x]=A[y];
    A[y]=t;
}

void print (int *A,int size){
    for(int i=1;i<=size;i++)cout<<A[i]<<" ";
    cout<<endl;
}

void reversal(int *A,int x,int y){
    int j=y;
    for(int i=x;i<=(x+y)/2;i++){
        //cout<<j<<endl;
        swap(A,i,j);
        j--;
    }
}



int reversal_number(int *A,int size){
    int reverses = 0;
    for(int i=1;i<=size;i++){
        if(A[i]==i)continue;
        int k = NULL_VALUE;

        for(int j=i;j<=size;j++){
            if(A[j]==i){
            k=j;
            //cout<<i<<" "<<k<<" "<<A[j]<<" "<<A[k]<<endl;
            break;
            }
        }

        if(A[k-1]-1==A[k]){
            reversal(A,i,k);
            print (A,size);
            reverses++;
        }
        else if(A[k-1]-1 != A[k] && A[k+1]-1 != A[k]){
            reversal(A,i,k);
            print(A,size);
            reverses++;
        }
        else if(A[k+1]-1==A[k]){
            int m;
            for(m=k;m<=size;m++){
                if(m+1>size)break;
                if(A[m]<A[m+1])continue;
                else break;
            }
            reversal(A,k,m);
            print(A,size);
            reversal(A,i,m);
            print(A,size);
            reverses+=2;
        }
    }
    return reverses;
}

int main(){
    int n;
    cin>>n;
    int A[n+2];
    A[0]=99999;
    A[n+1]=99999;
    for(int i=1;i<=n;i++){
        cin>>A[i];
    }
    cout<<endl;
    int answer = reversal_number(A,n);
    cout<<answer<<endl;
}

