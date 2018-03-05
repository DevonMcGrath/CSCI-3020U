/*


- The child process has a join on all threads and after all threads have
completed writes the total_sum to a file called sum.txt and terminates
- After the child process has terminated the parent process reads the
contents of sum.txt and prints the total sum.-
Reading and writing files between processes is one of the simplest
methods of IPC
*/

/*
- Prompts a user for fives numbers
- For each number creates a thread
- Each thread executes a function factorial which takes a struct containing
the number and index of the number entered (0 - 4) and does the
following:
- Calculates the factorial (e.g. 5! = 5x4x3x2x1 = 120, 0! = 1).
- Using a semaphore, gets the previous value in the
moving_sum[index-1] if the value at that index is > 0. If the value
is retrieved it is added to the factorial calculated and the sum is
added to moving_sum[index].
- Until the value in moving_sum[index-1] is > 0, performs an infinite
loop, each time it must perform signal and wait to allow other
threads access to the critical section.
- After all threads finish (using join()) print the contents of moving_sum
*/

#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define BUFFER_LEN 256

int total_sum=0;
int number_cnt=5;
sem_t sem;


void* factorial (void* args){
  int factorial_sum = 1;
  int* input = args;

  for (int i = 1; i<=*input;i++){
    factorial_sum *= i;
  }

  sem_wait(&sem);
  total_sum+=factorial_sum;
  printf("current total sum %d, current factorial %d\n",total_sum,factorial_sum);
  sem_post(&sem);

  return 0;
}


int main(void){
  pthread_t threads[number_cnt];
  pid_t pid;

  FILE* fp= fopen("numbers.txt","w");
  for (int i =0;i<number_cnt;i++){
    printf("%s\n","Enter number");
    int input;
    scanf("%d", &input);
    fprintf(fp,"%d\n",input);
  }
  fclose(fp);
  pid=fork();
  printf("%d\n",pid);

if (pid==0){//child
      sem_init(&sem,0,1);

      fp= fopen("numbers.txt","r");
      int inputs[number_cnt];
      for(int i = 0; i < number_cnt; ++i){
        fscanf(fp,"%d",&inputs[i]);
        pthread_create(&threads[i], NULL,&factorial,&inputs[i]);
      }
      fclose(fp);

      for (int i=0;i<number_cnt;i++){
        pthread_join(threads[i], NULL);
      }

      sem_destroy(&sem);

      fp= fopen("sum.txt","w");
      fprintf(fp,"%d",total_sum);
      fclose(fp);
      exit(0);
  }else{
      int returnStatus;
      waitpid(pid, &returnStatus, 0);  // Par
  }

  //back to 1 process
  fp= fopen("sum.txt","r");
  int out;
  fscanf(fp,"%d",&out);
  printf("total sum: %d\n",out);
  fclose(fp);
}
