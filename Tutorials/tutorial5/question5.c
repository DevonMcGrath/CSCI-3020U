#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_barrier_t barrier;
pthread_mutex_t lock;
int grade_cnt=10;
float grades[10];
float total_grade;
float total_bellcurve;

void* read_grades(void* arg){
  //read grades from grades.txt
  printf("%s\n","read grades" );

  FILE *fp;
  fp = fopen("grades.txt", "r");
  for (int i=0;i<grade_cnt;i++){
    fscanf(fp,"%f",&grades[i]);
  }
  fclose(fp);
  pthread_barrier_wait(&barrier);
}

void *save_bellcurve(void* args){

  pthread_mutex_lock(&lock);
  printf("%s\n","save bell curve" );
  float* grade = args;
  total_grade+= *grade;
  float bell_cureved_grade = *grade*1.50f;
  total_bellcurve+= bell_cureved_grade;
  FILE *fp;
  fp = fopen("bellcurve.txt", "a");
  fprintf(fp,"%.2f\n",bell_cureved_grade);
  fclose(fp);
  pthread_mutex_unlock(&lock);

}

int main(void){
  int student_cnt=10;
  int err;
  total_grade=0;
  total_bellcurve=0;
  pthread_t read_grades_thread;
  pthread_barrier_init(&barrier, NULL, 2);
  pthread_create(&read_grades_thread, NULL, read_grades,NULL);
  pthread_barrier_wait(&barrier);

  printf("%s\n","past barrier wait" );
  int cnt=0;
  pthread_t student_thread[student_cnt];
  while(cnt<student_cnt){
    err = pthread_create(&student_thread[cnt], NULL, save_bellcurve,&grades[cnt]);
    if(err==0){
      cnt++;
    }
  }
  pthread_barrier_destroy(&barrier);
  pthread_join(read_grades_thread, NULL);
  for (int i=0;i<student_cnt;i++){
      pthread_join(student_thread[i], NULL);
    }

    printf("Before bellcruve: Total grade: %f class average: %f\n",total_grade,total_grade/student_cnt);
    printf("After bellcruve: Bell curved grade grade: %f class average: %f\n",total_bellcurve,total_bellcurve/student_cnt);

    pthread_mutex_destroy(&lock);

}
