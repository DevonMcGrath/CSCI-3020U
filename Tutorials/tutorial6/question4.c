#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define NUMBERS 10
int buffer_len =5;
int buffer[5] = {0};

sem_t sem;

//add to buffer_len
void* producer(void* arg){
  int* arr = (int*)arg;
  int produced_cnt =0;
  while(produced_cnt<NUMBERS){
    //if too large wait for the consumer
    sem_wait(&sem);
    if(buffer_len<5){
      buffer[buffer_len] = arr[produced_cnt];
      printf("Produced %d\n",buffer[buffer_len]);
      buffer_len++;

      int sleep_len = rand() % 3;
      sleep(sleep_len);
      produced_cnt++;
    }
      sem_post(&sem);

  }
  return 0;
}

void* consumer(void* arg){
  int consumed_cnt =0;
  while(consumed_cnt<NUMBERS){
    sem_wait(&sem);
    //wait and allow producer to go
    if(buffer_len>0){
      printf("Consumed: %d\n", buffer[buffer_len-1]);
      buffer[buffer_len]=0;
      buffer_len--;
      consumed_cnt++;

      int sleep_len = rand() % 3;

    sleep(sleep_len) ;
  }
    sem_post(&sem);
  }
  return 0;
}


int main(void){
  pthread_t consumer_thread;
  pthread_t producer_thread;
  time_t t;
  srand((unsigned) time(&t));


  //hold entered numbers
  int arr[NUMBERS];
  for (int i =0;i<NUMBERS;i++){
      printf("%s\n","Enter Number");
      scanf("%d",&arr[i]);
    }

    buffer_len=0;
    sem_init(&sem, 0, 1);

    pthread_create(&producer_thread, NULL, &producer, &arr);
    pthread_create(&consumer_thread, NULL, &consumer, NULL);

    pthread_join(producer_thread,NULL);
    pthread_join(consumer_thread,NULL);

    sem_destroy(&sem);
}
