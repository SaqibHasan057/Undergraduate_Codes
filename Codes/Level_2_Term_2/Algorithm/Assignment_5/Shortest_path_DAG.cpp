#include <iostream>
#include <stdio.h>
#include "LinkedList.cpp"
#include "Queue.cpp"
#define INFINITY 99999
#define NULL_VALUE -99999
using namespace std;

int getNextVertex(int *array,int size){
    for(int i=0;i<size;i++){
        if(array[i]==0){
            array[i]=NULL_VALUE;
            return i;
        }
    }
    return NULL_VALUE;
}

int printArray(int *array,int size){
    for(int i=0;i<size;i++)cout<<array[i]<<" ";
    cout<<endl;
}


int main(){
    //FILE *fp = freopen("input1.txt","r",stdin);
    int V,E;
    cout<<"Enter number of vertices: "<<endl;
    cin>>V;
    cout<<"Enter number of edges: "<<endl;
    cin>>E;

    linkedList adj[V];
    int topo[V];
    int indegree[V];
    int distance[V];

    for(int i=0;i<V;i++){
        indegree[i]=0;
        topo[i]=0;
        distance[i]=INFINITY;
    }

    for(int i=0;i<E;i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].addNode(b,c);
        indegree[b]++;
    }

    //printArray(indegree,V);

    Queue Q;
    int position =0;

    for(int i=0;i<V;i++){
        if(indegree[i]==0){
            Q.enqueue(i);
        }
    }

    while(!Q.empty()){
        int u = Q.dequeue();
        topo[position]= u;
        position++;
        Node *iterate = adj[u].getIterator();
        while(iterate!=0){
            int v =iterate->getData();
            indegree[v]--;
            if(indegree[v]==0)Q.enqueue(v);
            iterate=iterate->getNext();
        }
    }

    int source;
    cout<<"Enter source:"<<endl;
    cin>>source;

    distance[topo[source]]=0;

    for(int i=source;i<V;i++){
        int u=topo[i];
        //cout<<u<<endl;
        Node *iterate = adj[u].getIterator();
        while(iterate!=0){
            int v = iterate->getData();
            int w = iterate->getWeight();
            if(distance[v]>distance[u]+w)distance[v]=distance[u]+w;
            iterate=iterate->getNext();
        }
    }
    printArray(topo,V);
    printArray(distance,V);
}

