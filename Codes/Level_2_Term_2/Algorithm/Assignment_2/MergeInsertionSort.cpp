#include <iostream>
#include <stdio.h>
using namespace std;
void InsertionSort(int A[],int low,int high,int size){
    for(int j=low+1;j<=high;j++){
        int key = A[j];
        int i = j-1;
        while(i>=low && A[i]>key)
        {
            A[i+1]=A[i];
            i--;
        }
        A[i+1]=key;
    }
}

void Merge(int A[],int low,int mid,int high){
    int left=mid-low+1;
    int right =high-mid;
    int L[left];
    int R[right];
    for(int i=0;i<left;i++)L[i] = A[low+i];
    for(int i=0;i<right;i++)R[i] = A[mid+1+i];
    int leftCount = 0;
    int rightCount = 0;
    int k = low;
    while(leftCount<left && rightCount<right){
        if(L[leftCount]<R[rightCount]){
            A[k++] = L[leftCount++];
        }
        else A[k++] = R[rightCount++];
    }
    while(k<=high){
        if(leftCount<left){
            A[k++] = L[leftCount++];
        }
        else if(rightCount<right){
            A[k++] = R[rightCount++];
        }
    }
}

void MergeSort(int A[],int low,int high){
    int length = high-low+1;
    if(low<high && length>14) {
        cout<<length<<endl;
        int mid = (low+high)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        Merge(A,low,mid,high);
    }
    else{
        InsertionSort(A,low,high,length);
    }
}

int main(){
    FILE *fp = freopen("input.txt","r",stdin);
    int n;
    cin>>n;
    int A[n];
    for(int i=0;i<n;i++)cin>>A[i];
    MergeSort(A,0,n-1);
    for(int i=0;i<n;i++)cout<<A[i]<<" ";
    cout<<endl;
    fclose(fp);
}


