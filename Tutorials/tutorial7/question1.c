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
/*

- Create a linked list structure called queue, which contains the following:
- process, an instance of your proc structure-
-
-
-
-
- next, a pointer to the next linked list structure initialized to NULL
Create a function: push(proc process), which is used to add each
process to the linked list (queue).
Your program then reads the contents of a file called processes.txt (10
LINES), which contains a comma separated list of the name, priority, pid,
and runtime.
For each entry read from processes.txt create an instance of the proc
struct and add it to the linked list using the push() function.
After all processes have been added to the linked list, iterate through it
and print the name, priority, pid, runtime of each process.
See the following for more information on linked lists: http://www.learn-
c.org/en/Linked_lists
*/
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

void push(proc_t* process){
  queue_t* current = linked_list;

   while (current->next != NULL) {
       current = current->next;
   }

   /* now we can add a new variable */
   current->next = malloc(sizeof(queue_t));
   current->process = *process;
   current->next->next = NULL;
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
  linked_list = NULL;
  linked_list = malloc(sizeof(queue_t));


  FILE* fp = fopen("processes.txt","r");
  while(1){
    proc_t* new_proc= malloc(sizeof(proc_t));
    char* token;
    char buff[BUFFER_LEN];

    fgets(buff,BUFFER_LEN,fp);
    char* line= strtok(buff,"\n");
    //get proc name
    token = strtok(line,", ");
    strcpy(new_proc->name,token);
    //get proc priority
    token= strtok(NULL," ,");
    if(token==NULL){
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




}
