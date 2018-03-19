#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define BUFFER_LEN 256

typedef struct proc {
  char parent[BUFFER_LEN];
  char name[BUFFER_LEN];
  int priority;
  int memory;
}proc_t;

typedef struct proc_tree {
  proc_t* process;
  struct proc_tree* left;
  struct proc_tree* right;

}proc_tree_t;

proc_tree_t* tree;


//crawl left to right approach
void add (proc_t* process){
  proc_tree_t* current = tree;

  if (current->process==NULL){
    current->process = malloc(sizeof(proc_t));
    current->process = process;
    current->left = NULL;
    current->right = NULL;
    return;
  }


  while (current->process != NULL) {
    //crawl until a left or right node is null
    //crawl left
    if(strcmp(current->process->name, process->parent)==0 ){
      if(current->left == NULL){
        current->left = malloc(sizeof(proc_tree_t));
        current= current->left;
        break;
      }else if(current->right == NULL){
        current->right = malloc(sizeof(proc_tree_t));
        current= current->right;
        break;
      }else{
        printf("%s\n","ERROR NO LEAF SPACE");
        exit(0);
      }
    }
    else{//names not equal
      if(strcmp(current->process->name,process->parent)<0){
        if(current->left == NULL){
          //allocate space
          current->left = malloc(sizeof(proc_tree_t));
          current= current->left;
          break;
        }else{
          current= current->left;
        }
      }
      else {//move right
        //allocate space
        if(current->right == NULL){
          current->right = malloc(sizeof(proc_tree_t));
          current= current->right;
          break;
        }else{
          current= current->right;
        }
    }
  }
}

  //tree node is null
  current->process = malloc(sizeof(proc_t));
  current->process = process;
  current->left = NULL;
  current->right = NULL;

  return;
}

int depth =0;


void print_node(proc_t* value) {
  for(int i=0; i < depth;i++){printf("\t");}
  printf("parent %s\n",value->parent);
  for(int i=0; i < depth;i++){printf("\t");}
  printf("name %s\n",value->name);
  for(int i=0; i < depth;i++){printf("\t");}
  printf("priority %d\n",value->priority);
  for(int i=0; i < depth;i++){printf("\t");}
  printf("memory %d\n",value->memory);
  printf("\n");

  return;
}

//go all the way left until a node is null
//when a node is null go back 1 and check right side
void recursive_iterate(proc_tree_t* current){

  if(current==NULL){
    return;
  }
  depth++;
  recursive_iterate(current->left);
  depth--;
    print_node(current->process);
    depth++;
recursive_iterate(current->right);
depth--;

  return;
}


void print_tree(proc_tree_t* current){
  recursive_iterate(current);
}



int main(void){
  tree = malloc(sizeof(proc_tree_t));
  tree->process = NULL;
  tree->left =NULL;
  tree->right = NULL;

  FILE* fp = fopen("processes_tree.txt","r");
  while(1){
    proc_t* new_proc= malloc(sizeof(proc_t));
    char* token;
    char buff[BUFFER_LEN];

    fgets(buff,BUFFER_LEN,fp);
    char* line= strtok(buff,"\n");
    if(line==EOF){
      break;
    }
    //get proc name
    token = strtok(line,", ");
    strcpy(new_proc->parent,token);

    //get proc name
    token = strtok(NULL,", ");

    if(token==NULL){
      free(new_proc);
      break;
    }
    strcpy(new_proc->name,token);

    //get proc priority
    token= strtok(NULL," ,");
    sscanf(token,"%d",&new_proc->priority);

    //get proc memory
    token= strtok(NULL," ,");
    sscanf(token,"%d",&new_proc->memory);

    add(new_proc);
  }
  fclose(fp);

  proc_tree_t* current = tree;

  print_tree(current);


}
