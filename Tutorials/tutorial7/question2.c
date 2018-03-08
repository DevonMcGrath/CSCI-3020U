#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_LEN 256

typedef struct proc{
  char name[BUFFER_LEN];
  int priority;
  int pid;
  int runtime;
}proc_t;

typedef struct queue{
  struct proc process;
  struct queue* next;

}queue_t;

queue_t* linked_list;

//push to end of the queue
void push(proc_t* process){
  queue_t* current = linked_list;

  while (current->next!= NULL) {
     current = current->next;
  }
  //current is now NULL
  current->next = malloc(sizeof(queue_t));
  current->process = *process;
  current->next->next = NULL;
  printf("added: %s\n",  current->process.name);
}

//remove first element in linked list
proc_t* pop(){
    proc_t* retval =  malloc(sizeof(proc_t));
    queue_t* next_node = NULL;

     if (linked_list == NULL) {
         return NULL;
     }
     next_node = linked_list->next;
     *retval = linked_list->process;
     linked_list= next_node;
     return retval;
}

proc_t* delete_name(char* name){
  queue_t* current = linked_list;
  proc_t* return_proc = malloc(sizeof(proc_t));
  if(current==NULL){
    return NULL;
  }

  while (current->next != NULL) {
      if(strcmp(current->next->process.name,name)==0){
        *return_proc = current->next->process;
        //go two ahead
        current->next = current->next->next;
        return return_proc;
      }
      current=current->next;
  }
  return NULL;

}
proc_t* delete_pid(int pid){
  queue_t* current = linked_list;
  proc_t* return_proc = malloc(sizeof(proc_t));
  if(current==NULL){
    return NULL;
  }

  while (current->next != NULL) {
      if(current->next->process.pid==pid){
        *return_proc = current->next->process;
        //go two ahead
        current->next = current->next->next;
        return return_proc;
      }
      current=current->next;
  }
  return NULL;
}

void print_all(){
  queue_t * current = linked_list;
   while (current->next != NULL) {
     printf("name: %s \n",current->process.name);
     printf("priority: %d \n",current->process.priority);
     printf("pid: %d \n",current->process.pid);
     printf("runtime: %d \n",current->process.runtime);
     printf("\n");
     current = current->next;
   }
   /* now we can add a new variable */
}

int main(void){
  linked_list = malloc(sizeof(queue_t));
  linked_list->next=NULL;

  FILE* fp = fopen("processes.txt","r");
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
    strcpy(new_proc->name,token);
    //get proc priority
    token= strtok(NULL," ,");
    if(token==NULL){
      free(new_proc);
      break;
    }

    sscanf(token,"%d",&new_proc->priority);
    //get proc pid
    token= strtok(NULL," ,");

    sscanf(token,"%d",&new_proc->pid);
    //get proc nuntime
    token= strtok(NULL," ,");
    sscanf(token,"%d",&new_proc->runtime);

    push(new_proc);
  }
  fclose(fp);
  print_all();
  proc_t* poped = pop();
  printf("poped name: %s\n",poped->name);

  printf("try to delete_pid:\n");
  proc_t*deleted=delete_pid(9223);
  printf("delete_pid: %s\n",deleted->name);

  poped=delete_name("eclipse");
  printf("delete_pid: %s\n",poped->name);

  print_all();
}
