#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void *bellcurve(void* grades){
  float *grade = grades;
  printf("bellcurved grade %.2f\n",*grade*1.50f);
}

int main(void){
  pthread_t tid[5];
  float grades[5];

  for (int i=0;i<5;i++){
    printf("Enter Student Grade\n");
    scanf("%f",&grades[i]);
  }

  for (int i=0;i<5;i++){
    pthread_create(&tid[i], NULL, bellcurve, &grades[i]);
  }

  for (int i=0;i<5;i++){
      pthread_join(tid[i], NULL);
      }


}
