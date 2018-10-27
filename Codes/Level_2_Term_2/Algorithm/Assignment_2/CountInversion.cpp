#include <iostream>
#include <stdio.h>
using namespace std;

int Merge(int A[],int low,int mid,int high){
    int count_inversion = 0;
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
        else{
            //cout<<L[leftCount]<<" "<<R[rightCount]<<endl;
            A[k++] = R[rightCount++];
            count_inversion+=left-leftCount;
        }
    }
    while(k<=high){
        if(leftCount<left){
            A[k++] = L[leftCount++];
        }
        else if(rightCount<right){
            A[k++] = R[rightCount++];
        }
    }
    return count_inversion;
}

int MergeSort(int A[],int low,int high){
    if(low<high){
        int mid = (low+high)/2;
        int left = MergeSort(A,low,mid);
        int right = MergeSort(A,mid+1,high);
        return Merge(A,low,mid,high)+left+right;
    }
    else return 0;
}

int main(){
    FILE *fp = freopen("input.txt","r",stdin);
    int n;
    cin>>n;
    int A[n];
    for(int i=0;i<n;i++)cin>>A[i];
    int count = MergeSort(A,0,n-1);
    for(int i=0;i<n;i++)cout<<A[i]<<" ";
    cout<<endl<<count<<endl;
    fclose(fp);
}


