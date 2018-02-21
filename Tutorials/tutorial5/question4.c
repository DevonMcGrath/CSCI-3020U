#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
- You MUST use mutual exclusion when incrementing total_grade
- Print the results of total grade, it should be the correct sum of all ten
grades.
*/

typedef struct student{
  char name[90];
  char id[20];
  float grade;

}student;

float total_grade;
pthread_mutex_t lock;

void *class_total(void * args){
  pthread_mutex_lock(&lock);
  float *grade = args;
  total_grade+=*grade;
  pthread_mutex_unlock(&lock);
}

int main(void){
  total_grade=0;
  int student_cnt=10;
  int cnt =0;
  int err;
  pthread_t tid[student_cnt];
  float grades[student_cnt];


  for (int i=0;i<student_cnt;i++){
    printf("Enter Student Grade\n");
    scanf("%f",&grades[i]);
  }


  while(cnt<student_cnt){
    err = pthread_create(&tid[cnt], NULL, class_total,&grades[cnt]);
    if(err==0){
      cnt++;
    }
  }

  for (int i=0;i<student_cnt;i++){
      pthread_join(tid[i], NULL);
    }

    printf("Total grade: %f\n",total_grade);
    pthread_mutex_destroy(&lock);

}
