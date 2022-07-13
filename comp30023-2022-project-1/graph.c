#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "FileOperations.c"

/*
A file that contains a graph structure that uses adjaceny list to store the system

A vertex in the graph consists of:
    1. currentFile - the vertex ID
    2. connectedFile - the egde between The first file of a process and the second file. Direction is from Current to Connected
    3. processidConnected - the edge label that states the which process has locked and requested these files above.
    4. time- time slot allocated used for challenge tash 
    5. isallocated - see if file is already allocated to a time slot for challenge
    6. next - pointer to the next node in the adjaceny list 


*/


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



//from the edges that represent each line of process file1 file2
//create a graph that represent the configuration.
Graph *createGraph(Edge edges[], Structure *s)
{

    Graph *graph = (Graph *)malloc(sizeof(graph));
    assert(graph != NULL);

    graph->adjacencyList = malloc(sizeof(Node *) * s->numUniqueFiles);
    assert(graph->adjacencyList != NULL);

    //initialise the head of each adjacency list to NULL.
    // since the vertex represent the files, numVertex = numUniqueFiles
    for (int i = 0; i < s->numUniqueFiles; i++)
    {

        graph->adjacencyList[i] = NULL;
    }

    //add the edges from a currentFile to a connectedFile
    //numEdges = numProcess, 
    for (int i = 0; i < s->numProcesses; i++)
    {

        int src = edges[i].src;
        int dest = edges[i].dest;
        int processid = edges[i].processid;

        Node *node = malloc(sizeof(Node));
        assert(node != NULL);
        node->currentFile = src;
        node->connectedFile = dest;
        node->processidConnected = processid;
        node->isallocated = 0;
        node->time = -1;
        
        //get the index to where should the head be located in the adjacency list by using the mapping made
        int index = getIndex(s, src);

        node->next = graph->adjacencyList[index];

        graph->adjacencyList[index] = node;
    }

    //for files that are not locked by any process but is requested, add to adjaceny list
    for (int i = 0; i < s->numUniqueFiles; i++)
    {

        if (graph->adjacencyList[i] == NULL)
        {
            // get the file that is pointed by the index of the adjacency list by the use of the mapping
            int fileNotIn = getFile(i, s);

            //create and add note to the respective index
            Node *node = malloc(sizeof(Node));
            assert(node != NULL);
            node->currentFile = fileNotIn;
            node->connectedFile = -1;
            node->processidConnected = -1;

            node->next = graph->adjacencyList[i];
            graph->adjacencyList[i] = node;
        }
    }

    return graph;
}


/*create an array of edges from the structure that is storing the system
First iterate through each process line and tokenise for each process its
requested and locked files.

The process id can be obtained with the same index since the array of the processid and that 
of the array that contains "file1 file2" are exactly the same with one only containing process id

*/

Edge *createEdges(Structure *s)
{

    Edge *edges = malloc(sizeof(Edge) * s->numUniqueFiles);
    assert(edges != NULL);

    for (int i = 0; i < s->numProcesses; i++)
    {

        char *currentProcessFiles = malloc(sizeof(char) * strlen(s->individualProcessFiles[i]));
        assert(currentProcessFiles != NULL);

        strcpy(currentProcessFiles, s->individualProcessFiles[i]);

        int file1 = atoi(strtok(currentProcessFiles, " "));
        int file2 = atoi(strtok(NULL, " "));
        int processid = atoi(s->processids[i]);

        edges[i].src = file1;
        edges[i].dest = file2;
        edges[i].processid = processid;
        edges[i].time = -1;
    }

    return edges;
}

void printGraph(Graph *graph, int numVertices, Structure *s)
{

    for (int i = 0; i < numVertices; i++)
    {

        Node *ptr = graph->adjacencyList[i];

        while (ptr != NULL)
        {
            printf("%d----%d----%d", graph->adjacencyList[i]->currentFile, graph->adjacencyList[i]->processidConnected, graph->adjacencyList[i]->connectedFile);

            ptr = ptr->next;
        }

        printf("=========next file===========\n");
    }
}


//traverse the graph to look for and resolve the deadlocks or to solve challenge 
//a flag of 1 implies that the traversal will resolve deadlocks 

/*
To find and resolve the deadlocks, DFS is used on the graph by having 2 visited arrays:
    1. One for storing the visited vertex from the adjacency list (visited)
    2. The other for the nodes that can be visited in the current DFS of a adjacencyList[i] (dfsVisited)

A variable is used to keep track of the minimum process id of each cycle with an intial value of 
2^ 32 + 1

for each of the head of the adjacency list, dfs is applied and looks for cycle and for a current
cycle, if an id is smaller than the current one, the latter is replaced.

After DFS has been carried out for adjacencyList[i] the whole dfsVisited array is reseted to unvisited.

when a cycle is found, the process with the minimum id is returned.


*/
void traverseGraph(Graph *graph, int numVertices, Structure *s, int flag)
{

    int visited[numVertices];
    int dfsVisited[numVertices];

    for (int i = 0; i < numVertices; i++)
    {
        visited[i] = 0;
        dfsVisited[i] = 0;
    }

    for (int i = 0; i < numVertices; i++)
    {   
        if (flag)
        {
            if (!visited[i])
            {

                long min = pow(2, 32) + 1;
                //dfs current node
                if (visitDFS(graph, i, visited, dfsVisited, &min, s))
                {
                    printf("%ld ", min);
                }

                //reset dfs array
                for (int j = 0; j < numVertices; j++)
                {
                    dfsVisited[j] = 0;
                }
            }
        }
    }
    

        
    }

//DFS a current node to look for the cycles.
int visitDFS(Graph *graph, int nodeToVisit, int *visited, int *dfsVisited, long *minProcess, Structure *s)
{

    visited[nodeToVisit] = 1;
    dfsVisited[nodeToVisit] = 1;
    if (graph->adjacencyList[nodeToVisit]->processidConnected < *minProcess)
        *minProcess = graph->adjacencyList[nodeToVisit]->processidConnected;

    if (graph->adjacencyList[nodeToVisit]->connectedFile == -1)
        return 0;

    Node *node;

    for (node = graph->adjacencyList[nodeToVisit]; node != NULL; node = node->next)
    {
        //use mapping to get the index in the adjaceny list
        int connectedIndex = getIndex(s, graph->adjacencyList[nodeToVisit]->connectedFile);

        //if the node that is connected has not been visited then visit the node and check if it is a cycle
        if (!visited[connectedIndex])
        {

            if (visitDFS(graph, connectedIndex, visited, dfsVisited, minProcess, s))
            {
                //cycle has been found
                return 1;
            }
        }

        //node has already been visited in the current dfs. Cycle found
        else if (dfsVisited[connectedIndex])
        {   
            //cycle has been found.
            return 1;
        }
    }

    //mark as unvisited
    dfsVisited[nodeToVisit] = 0;
    return 0;
}



//variable to keep the timeslot
int timeslot = 0;


/*
    Function to schedule the processes to a timeslot.

    In order to schedule the processes to a time slot, the edges of the graph is used since 
    the edges represent a process line.

    All edges initally has a timeSlot of -1 implying that the former has not been allocated to an edge.

    The src of an edge is the first file of a process and dest is the second file.
    They are copied into firstFile and secondFile respectively.

    The algorithm to schedule is as follows:

    1. Loop through the array of edges and for each iteration create an array that will contains
        all the files that has been added in the current timeslot.

    2. check if the edge[i] has been allocated a timeslot. If not then allocate to current timeslot.

    3. add the files of the edge to the currentTimeSlot array.

    4. for the edge[i], iterate through the edges.

    5. if edge[j] != -1 skip this iteration as that process has been allocated a timeslot.

    6. else check if the one or both files of edges[j] is already present in the currentTimeSlot array.

    7. if one or both is present then skip edge[j] as it cannot be allocated to the current timeSlot.

    8. if one or both are not present, add that edge to the same timeslot and add the files of edge[j]
        to the currentTimeSlot array.
    
    9. After the iteration of edge[i] over the array is finished increment the timeslot and repeat 2-8 for the next edge[i].

*/
void doChallenge(Edge edges[], Structure* s){

    int firstFile; 
    int secondFile;
   

    for(int i = 0;  i < s->numProcesses; i ++){

        int filesinCurrentTimeSlot[s->numUniqueFiles];
        int indexTimeSlotArray =0;
    
        firstFile = edges[i].src;
        secondFile = edges[i].dest;

        if(edges[i].time == -1){ 
            
            edges[i].time = timeslot;
            filesinCurrentTimeSlot[indexTimeSlotArray++] = firstFile;
            filesinCurrentTimeSlot[indexTimeSlotArray++] = secondFile;
            
            
        }

        for(int j = 0; j < s->numProcesses; j++){

            if(edges[j].time != -1){
                continue;
            }

            else{
               int both = 0;

               for(int k = 0; k < indexTimeSlotArray; k++){

                   if(filesinCurrentTimeSlot[k] == edges[j].src ||filesinCurrentTimeSlot[k] == edges[j].dest){
                       both++;
                   }
               }

               if(!both){
                   edges[j].time = timeslot;
                   filesinCurrentTimeSlot[indexTimeSlotArray++] =  edges[j].src;
                   filesinCurrentTimeSlot[indexTimeSlotArray++] =  edges[j].dest;

               }
            }


        }
        timeslot++;
            
    }
    timeslot = 0;
    for(int i = 0;  i < s->numProcesses; i ++){
        if(edges[i].time > timeslot) timeslot =edges[i].time; 
        printf("%d %d %d %d\n", edges[i].time,edges[i].processid,edges[i].src,edges[i].dest);
    }
    printf("Simulation time %d\n",timeslot+1);


}



void freeEdges(Edge *edges, int numEdges)
{

    free(edges);
}

void freeGraph(Graph *graph, int numVertices)
{

    for (int i = 0; i < numVertices; i++)
    {

        Node *node = graph->adjacencyList[i];
        Node *tmp;

        while (node != NULL)
        {

            tmp = node->next;
            free(node);
            node = tmp;
        }

       
    }
}