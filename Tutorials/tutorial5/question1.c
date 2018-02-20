#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
- Creates two threads, the first uses a function hello_world() which prints
hello world, the second uses a function goodbye() which prints goodbye.
- Each function has a random sleep duration before printing the output
- After running your program a few times you should notice that the order of
hello world and goodbye being printed to the screen is not consistent, as
each thread is executing independently.
*/
void *hello_world(void *vargp){
  sleep(rand() % 2);
  printf("Hello World\n");
}

void goodbye(void* vargp){
  sleep(rand() % 2);
  printf("goodbye\n");
}

int main(void){
  srand(time(NULL));   // should only be called once
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, hello_world, NULL);
  pthread_create(&tid2, NULL, goodbye, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

}
