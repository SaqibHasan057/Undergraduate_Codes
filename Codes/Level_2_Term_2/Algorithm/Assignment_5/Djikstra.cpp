#include <iostream>
#include <stdio.h>
#include "MinHeap.cpp"
#include "linkedList.cpp"
#define INFINITY 99999

int printArray(int *array,int size){
    for(int i=0;i<size;i++)cout<<array[i]<<" ";
    cout<<endl;
}

int main(){

    //FILE *fp = freopen("input2.txt","r",stdin);
    int directed = 0;
    int V,E;
    cout<<"Press 1 if directed: ";
    cin>>directed;
    cout<<"Enter number of vertices: ";
    cin>>V;
    cout<<"Enter number of edges: ";
    cin>>E;

    linkedList adj[V];
    heapNode heapArray[V];
    int posArray[V];
    int distance[V];

    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].addNode(b,c);
        if(directed==0)adj[b].addNode(a,c);
    }
    //cout<<"processing"<<endl;

    for(int i=0;i<V;i++){
        heapNode node(i,INFINITY);
        heapArray[i]=node;
        posArray[i]=i;
        distance[i]=INFINITY;
    }

    int source;
    minHeap q(heapArray,posArray,V);

    cin>>source;


    q.changeKey(source,0);
    distance[source]=0;

    cout<<endl;

    for(int i=0;i<V;i++)adj[i].printList();


    while(q.getLength()>0){
        heapNode minNode = q.extractMin();
        int u = minNode.getVertex();
        int dist = minNode.getDistance();
        distance[u]=dist;
        Node *iterate = adj[u].getIterator();
        while(iterate!=0){
            int v = iterate->getData();
            int w = iterate->getWeight();
            if(distance[v]>distance[u]+w){
                q.changeKey(v,distance[u]+w);
                distance[v]=distance[u]+w;
            }
            iterate = iterate->getNext();
        }
    }

    printArray(distance,V);

    return 0;








}
