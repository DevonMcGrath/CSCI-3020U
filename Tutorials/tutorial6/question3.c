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

int array_size=5;
int moving_sum[5];
sem_t can_move;

struct data {
  int number;
  int index;
};

void* factorial (void* args){
  int factorial_sum = 1;
  struct data* input = args;
  int index = input->index;

  for (int i = 2 ;i <=input->number;i++){
    factorial_sum *= i;
  }

  sem_wait(&can_move);
  int sem_val;
  sem_getvalue(&can_move,&sem_val);

  if(index>0){
    factorial_sum+=moving_sum[index-1];
    moving_sum[index]=factorial_sum;

    while(moving_sum[index]<=0){
      sem_post(&can_move);
    }

  }
  sem_post(&can_move);
}


int main(void){
  pthread_t threads[array_size];

  for (int i =0;i<array_size;i++){
    moving_sum[i]=0;
  }
  sem_init(&can_move, 0, 1);

  for (int i =0;i<array_size;i++){
    printf("%s\n","Enter number");
    struct data input;
    input.index=i;
    scanf("%d", &input.number);
    pthread_create(&threads[i], NULL, factorial,&input);
  }

  for(int i = 0; i < array_size; ++i){
    pthread_join(threads[i], NULL);
    printf("%s index: %d :value: %d\n","moving_sum",i,moving_sum[i]);
  }

  sem_destroy(&can_move);



}
