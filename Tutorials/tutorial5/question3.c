#define _XOPEN_SOURCE 600 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
- Creates five threads, one for each student.
- Create a struct named student containing three members, name
student_id, and grade.
- Create a function bellcurve(student) which takes a student (the struct
type) as an argument and bellcurves the grades by multiplying it by 1.50
and prints the student name, id, and bellcurved grade to the terminal.
- The program must create the 5 threads and initialize them only after
receiving all 5 grades.
*/

typedef struct student{
  char name[90];
  char id[20];
  float grade;

}student;

void *bellcurve(void* arg){
  struct student* s = arg;
  printf("bellcurved grade %.2f\n",s->grade*1.50f);
}

int main(void){
  int student_cnt=5;
  pthread_t tid[student_cnt];
  struct student students[student_cnt];

  for (int i=0;i<student_cnt;i++){
    printf("Enter Student Name\n");
    scanf("%s",students[i].name);
    printf("Enter Student ID\n");
    scanf("%s",students[i].id);
    printf("Enter Student Grade\n");
    scanf("%f",&students[i].grade);
  }

  for (int i=0;i<student_cnt;i++){
    pthread_create(&tid[i], NULL, bellcurve, &students[i]);
  }

  for (int i=0;i<student_cnt;i++){
      pthread_join(tid[i], NULL);
    }
}
