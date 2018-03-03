#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUMBERS 7
int buffer_len =5;
int buffer[5] = {0};

sem_t sem;

//add to buffer_len
void* producer(void* arg){
  int* arr = (int*)arg;

  for (int i =0; i< NUMBERS;i++){
    //if too large wait for the consumer
    sem_wait(&sem);

    if(buffer_len< 4){
      printf("buffer_len too large\n");

      buffer[i] = arr[i];
      buffer_len++;
      printf("Produced %d\n",buffer[i]);

      float sleep_len = (rand() % 5) / 10.0;
      printf("producer sleep: %f\n",sleep_len);
      sleep((rand() % 5) / 10.0) ;
    }
    //wake up consumer
      sem_post(&sem);

  }
  return 0;
}

void* consumer(void* arg){
  int consumed_cnt =0;
  while(consumed_cnt<10){
    sem_wait(&sem);

    //wait and allow producer to go
    if(buffer_len>=0){
      printf("buffer_len too small\n");

      printf("consumer buffer_len: %d\n", buffer_len);
      printf("Consumed: %d\n", buffer[buffer_len]);
      buffer[buffer_len]=0;
      buffer_len--;

      float sleep_len =(rand() % 5) / 10.0;
      sleep(sleep_len) ;
      consumed_cnt++;
    }
    sem_post(&sem);


  }
  return 0;
}


int main(void){
  pthread_t consumer_thread;
  pthread_t producer_thread;

  //hold entered numbers
  int arr[NUMBERS];
  for (int i =0;i<NUMBERS;i++){
      printf("%s\n","Enter Number");
      scanf("%d",&arr[i]);
    }

    buffer_len=0;
    sem_init(&sem, 0, 0);

    pthread_create(&producer_thread, NULL, &producer, arr);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);

    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    sem_destroy(&sem);
}
