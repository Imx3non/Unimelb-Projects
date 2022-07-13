/********************************************/
// This file contains the main function of the
// program, which reads command line inputs
// and check for deadlocks and resolve them
// or calculate the execution time

// Rajneesh Gokool
// Student ID: 1101512
// Subject Name: Computer Systems
// Subject Code: COMP30023

/*********************************************/



#include <unistd.h>
#include "graph.c"

Structure s;

void freeStructure(Structure *s);
void initialAllocation(Structure *s);
void allocateSpace(Structure *s);
FILE * openfile(char* path);



int main(int argc, char *argv[])
{


    int execution = 0;
    int challenge = 0;
    int c;

    //get the flags for challenge and execution
    while( ( c = getopt(argc,argv,"fec")) != -1){

        switch (c){

            case 'e':
                execution = 1;
                break;
            case 'c':
                challenge = 1;
                break;

            default:
            ;
        }   
 

    }
    //the file will always be the index that was left out by getopt()
    FILE *fp = openfile(argv[optind]);

    //allocate strucutre to count process lines
    initialAllocation(&s);

    countProcess(fp, &s);
    fclose(fp);

    fp = openfile(argv[optind]);

    //allocate spcae to get the exact space required by the system after number of processes was counted
    allocateSpace(&s);

    //fill data structure
    readFile(fp, &s);
    fclose(fp);

   
    //no challenge flag
    if(!challenge){
        printf("Processes %d\n", s.numProcesses);
        printf("Files %d\n", s.numUniqueFiles);

        //execution flag
        if(execution){
            getExecution(&s);
        }
        
        //no execution flag
        else{  
            if(checkDeadlock(&s)){

                printf("Deadlock detected\n");
                Edge* edges = createEdges(&s);
                getUniqueFiles(&s);
                Graph* graph = createGraph(edges,&s); 
                printf("Terminate ");
                traverseGraph(graph,s.numUniqueFiles,&s,1);
                freeEdges(edges,s.numProcesses);
                freeGraph(graph,s.numUniqueFiles);
                printf("\n");
            }

            else{
                printf("No deadlocks\n");
         
            }

        }
    }

    //challenge flag
    else{
        
        Edge* edges = createEdges(&s);
        getUniqueFiles(&s);
        doChallenge(edges,&s);
        freeEdges(edges,s.numProcesses);
    }
    freeStructure(&s);
    

}



FILE * openfile(char* path){

    FILE* fp = fopen(path,"r");

    if(fp == NULL){
        printf("File not found!\n");
        exit(0);
    }

    return fp;
}


