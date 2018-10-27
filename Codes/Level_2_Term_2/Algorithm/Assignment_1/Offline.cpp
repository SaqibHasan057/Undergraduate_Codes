#include <iostream>
#include <cstdlib>
using namespace std;

class VW{
    int itemNo;
    float value;
public:
    VW(){
        itemNo=0;
        value=0;
    }
    VW(int itemNo,float value){
        this->itemNo=itemNo;
        this->value=value;
    }
    int getItemNo(){return itemNo;}
    float getValue(){return value;}
};

/*Functions for Heap starts here*/
void Max_Heapify(VW A[],int size,int i){
    int l=2*i+1;
    int r=2*i+2;
    int largest;

    if(l<size && A[l].getValue()>A[i].getValue())largest=l;
    else largest=i;

    if(r<size && A[r].getValue()>A[largest].getValue())largest=r;

    if(largest!=i){
        VW hold;
        hold=A[largest];
        A[largest]=A[i];
        A[i]=hold;
        Max_Heapify(A,size,largest);
    }

}

void Build_Max(VW A[],int size){
    for(int i=size/2;i>=0;i--)Max_Heapify(A,size,i);
}

VW Extract_Max(VW A[],int &size){
    if(size<=0)return VW(0,0);
    VW max = A[0];
    A[0]=A[size-1];
    size--;
    Max_Heapify(A,size,0);
    return max;
}

/*Functions to Heap Ends Here*/

int main(){
    int n;
    float C;
    cin>>n>>C;
    float W[n];
    float V[n];
    VW VbyW[n];
    for(int i=0;i<n;i++){
        cin>>W[i]>>V[i];
        VW add(i,V[i]/W[i]);
        VbyW[i] = add;
    }
    int heapSize = n;
    Build_Max(VbyW,heapSize);
    float maxValue=0;
    float current_Capacity = C;
    while(current_Capacity>0 && heapSize!=0){
        VW max = Extract_Max(VbyW,heapSize);
        float weight = W[max.getItemNo()];
        float value = V[max.getItemNo()];
        if(current_Capacity>=weight){
            cout<<"Item: "<<max.getItemNo()+1<<" Weight: "<<weight<<endl;
            maxValue+=V[max.getItemNo()];
        }
        else{
            float fracval = current_Capacity/weight;
            fracval*=value;
            cout<<"Item: "<<max.getItemNo()+1<<" Weight: "<<current_Capacity<<endl;
            maxValue+=fracval;
        }
        current_Capacity-=weight;
    }

    cout<<"Maximum Value: "<<maxValue<<endl;


}
