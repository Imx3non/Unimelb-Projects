/*
A file that contains a graph structure that uses adjaceny list to store the system
to check for cycles and solve the challenge.

A vertex in the graph consists of:
    1. currentFile - the vertex ID
    2. connectedFile - the egde between The first file of a process and the second file. Direction is from Current to Connected
    3. processidConnected - the edge label that states the which process has locked and requested these files above.
    4. time- time slot allocated used for challenge tash 
    5. isallocated - see if file is already allocated to a time slot for challenge
    6. next - pointer to the next node in the adjaceny list 


Rajneesh Gokool
Student ID: 1101512
Subject Name: Computer Systems
Subject Code: COMP30023

/*********************************************/


*/

#include "FileOperations.h"

typedef struct Node
{

    // node label
    int currentFile;
    int connectedFile;
    int processidConnected;
    int time;

    int isallocated;
    struct Node *next;
} Node;

typedef struct Graph
{
    Node **adjacencyList;

} Graph;

typedef struct Edge
{
    int src;
    int dest;

    // label the egde as the process
    int processid;  

    //timeslot for challenge
    int time;

} Edge;

void printGraph(Graph *graph, int numVertices, Structure *s);
int visitDFS(Graph *graph, int nodeToVisit, int *visited, int *dfsVisited, long *minProcess, Structure *s);
int dfsChallenge(Graph *graph, int nodeToVisit, int *visited, int *dfsVisited, int* time, Structure *s);
Graph *createGraph(Edge edges[], Structure *s);
Edge *createEdges(Structure *s);
void printGraph(Graph *graph, int numVertices, Structure *s);
void traverseGraph(Graph *graph, int numVertices, Structure *s, int flag);
int visitDFS(Graph *graph, int nodeToVisit, int *visited, int *dfsVisited, long *minProcess, Structure *s);
void doChallenge(Edge edges[], Structure* s);
void freeEdges(Edge *edges, int numEdges);