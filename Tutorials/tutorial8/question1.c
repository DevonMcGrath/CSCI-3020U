#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_LEN 256

typedef proc struct{
  char parent[BUFFER_LEN];
  char name[BUFFER_LEN];
  int priority;
  int memory;
}proc_t;

typedef  proc_tree struct{
  proc* tree;
}

void add (proc process){

}

void iterate(proc_tree tree){

}

/*
Create the necessary functions to interact with your binary tree data
structure, you will need to add items to your tree and iterate through it.
Your program then reads the contents of a file called process_tree.txt (7
LINES), which contains a comma separated list of the parent, name,
priority, and memory.
Read the contents of the file and create your binary tree, add the children
to the parent based on the name of the parent.
Print the contents of your binary tree (you likely need to use recursion!)
displaying the contents of each parent, and the children of each parent.
*/






int main(void){



}
