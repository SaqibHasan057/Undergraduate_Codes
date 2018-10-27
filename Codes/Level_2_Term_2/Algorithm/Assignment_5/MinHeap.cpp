#include <iostream>
using namespace std;

class heapNode{
    int vertex;
    int distance;

public:
    heapNode(){
        this->vertex=0;
        this->distance=0;
    }
    heapNode(int vertex,int distance){
        this->vertex=vertex;
        this->distance=distance;
    }

    void setVertex(int vertex){
        this->vertex=vertex;
    }

    void setDistance(int distance){
        this->distance=distance;
    }

    int getVertex(){return vertex;}

    int getDistance(){return distance;}
};

class minHeap{
    heapNode *heap;
    int length;
    int *position;

public:


    minHeap(heapNode *array,int *arrayPos,int size){
        heap = array;
        length=size;
        position=arrayPos;
    }

    int parent(int i){return (i-1)/2;}
    int left(int i){return 2*i+1;}
    int right(int i){return 2*i+2;}
    int getLength(){return length;}

    void minHeapify(int i){
        int L = left(i);
        int R = right(i);
        int smallest;

        if(L<length && heap[L].getDistance()<heap[i].getDistance())smallest=L;
        else smallest=i;

        if(R<length && heap[R].getDistance()<heap[i].getDistance())smallest=R;

        if(smallest!=i){
            heapNode temp = heap[i];
            int u = heap[i].getVertex();
            int v = heap[smallest].getVertex();
            heap[i]= heap[smallest];
            heap[smallest]=temp;
            int tempo = position[u];
            position[u] = position[v];
            position[v] = tempo;
            minHeapify(smallest);
        }
    }

    void buildHeap(){
        for(int i=length/2;i>=0;i--){
            minHeapify(i);
        }
    }

    heapNode extractMin(){
        if(length>0){
            heapNode min = heap[0];
            heap[0]=heap[length-1];
            position[heap[0].getVertex()]=0;
            length--;
            minHeapify(0);
            return min;
        }
    }

    void changeKey(int i,int key){
        int j = position[i];
        int k = i;
        heap[j].setDistance(key);
        while(j>0 && heap[parent(j)].getDistance()>heap[j].getDistance()){
            int u = heap[j].getVertex();
            int v = heap[parent(j)].getVertex();
            int tempo = position[u];
            position[u] = position[v];
            position[v] = tempo;
            heapNode temp = heap[j];
            heap[j]=heap[parent(j)];
            heap[parent(j)]=temp;
            j=parent(j);
        }
    }

    void printHeap(){
        for(int i=0;i<length;i++){
            cout<<heap[i].getVertex()<<":"<<heap[i].getDistance()<<endl;
        }
    }

    void printPositionArray(){
        for(int i=0;i<length;i++){
            cout<<position[i]<<" ";
        }
        cout<<endl;
    }
};

/*int main(){
    heapNode heapArray[]={{new heapNode(0,999)},{new heapNode(1,999)},{new heapNode(2,99)}};
    int posArray[]={0,1,2};
    minHeap heaper(heapArray,posArray,3);
    heaper.printHeap();
}*/
