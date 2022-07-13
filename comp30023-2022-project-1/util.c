/*
File that contains helper functions

Rajneesh Gokool
Student ID: 1101512
Subject Name: Computer Systems
Subject Code: COMP30023

*/

//function to compare integeres and return 
// 0 if they are the same 
// 1 if a > b
// -1 if a < b
int cmpfunc(const void *a, const void *b)
{

    return (*(int *)a - *(int *)b);
}
