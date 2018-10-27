#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define WHITE 1
#define GREY 2
#define BLACK 3
#define NULL_VALUE -999999
#define INFINITY 999999


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color;
	int *parent;
	int *distance;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	int getIndegree(int n);
	bool deleteAllEdge(int u,int *array); //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color = 0;
	parent = 0;
	distance = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

int Graph::getIndegree(int n){
    int indegree = 0;
    for(int i=0;i<nVertices;i++){
        if(matrix[i][n]==1)indegree++;
    }
    return indegree;
}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;

}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(matrix[u][v]==1)return true;
    else return false;

}

bool Graph::deleteAllEdge(int u,int *array){
    if(u<0 || u>=nVertices) return false;
    for(int i =0;i<nVertices;i++){
            if(matrix[u][i]==1)array[i]--;
    }
    return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int degree = 0;
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i]==1)degree++;
    }
    return degree;
}

void Graph::printAdjVertices(int u)
{
    //prints all adjacent vertices of a vertex u
    if(u<0 || u>=nVertices) return;
    for(int i=0;i<nVertices;i++){
        if(matrix[u][i]==1)printf("%d ",i);
    }
    printf("\n");
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0;i<nVertices;i++){
        if(matrix[v][i]== matrix[u][i] && matrix[v][i]==1 && matrix[u][i]==1)
        {
            return true;
        }
    }
    return false;
}

void Graph::bfs(int source)
{
    //write this function
    if(color!=0)delete[]color;
    color = new int[nVertices];
    if(parent!=0)delete[]parent;
    parent = new int[nVertices];
    if(distance!=0)delete[]distance;
    distance = new int[nVertices];

    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        distance[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    distance[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int u = q.dequeue();

        for(int i=0;i<nVertices;i++){
            int v;
            if(matrix[u][i]==1){
            v=i;
            if(color[v]==WHITE){
                distance[v]=distance[u]+1;
                color[v]=GREY;
                parent[v]=u;
                q.enqueue(v);
            }
            }
        }
        color[u]=BLACK;
    }
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return distance[v];
}



void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(matrix!=0)delete[]matrix;
    matrix=0;
}

int searchForZero(int *array,int size){
    for(int i=0;i<size;i++){
        if(array[i]==0){
            array[i]=NULL_VALUE;
            return i;
        }
    }
    return NULL_VALUE;
}




//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n,edges;
    Graph g(true);
    printf("Enter number of vertices and edges: ");
    cin>>n>>edges;
    g.setnVertices(n);

    for(int i=0;i<edges;i++){
        char A,B;
        cin>>A>>B;
        int C,D;
        C=A-'a';
        D=B-'a';
        g.addEdge(C,D);

    }

    /*g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,4);
    g.addEdge(3,4);
    g.addEdge(4,5);
    g.addEdge(4,6);
    g.addEdge(6,5);
    g.addEdge(2,3);
    g.addEdge(2,7);
    g.addEdge(3,6);
    g.addEdge(7,6);*/

    cout<<endl;
    //g.printGraph();

    int indegree[n];
    Queue qu;

    for(int i=0;i<n;i++)indegree[i]=0;

    for(int i=0;i<n;i++){
        indegree[i]=g.getIndegree(i);
    }

    qu.enqueue(searchForZero(indegree,n));
    int rank = 1;
    while(qu.empty()==false){
        int u = qu.dequeue();
        char x = 'a'+u;
        cout<<rank++<<":"<<x<<endl;
        g.deleteAllEdge(u,indegree);
        int push = searchForZero(indegree,n);
        if(push!=NULL_VALUE)qu.enqueue(push);
    }



}
