#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"
#include <assert.h>
#include "FileOperations.h"


int main(int argc, char** argv) {

    struct kdTree* root = NULL;


    FILE *fp = fopen(argv[1], "r");
    FILE *outputFile = fopen(argv[2], "w");
    assert(fp != NULL && outputFile != NULL);
    root = readFile(fp, root);
    radiusQuery(root,outputFile);
    fclose(outputFile);
    return 0;


}


