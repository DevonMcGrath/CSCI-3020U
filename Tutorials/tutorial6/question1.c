#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_LEN 256

int main(void)
{

pid_t f_id1=0;
pid_t f_id2=0;

f_id1= fork();

if (f_id1 == 1 ){
  f_id2 = fork();
}

//child process 1
if(f_id1 == 0 ){
  FILE* fp = fopen("child1.txt", "w" );
  fputs("child1.txt",fp);
  fclose(fp);
  sleep(1);
  char buff[BUFFER_LEN];

  fp = fopen("child1.txt", "r" );
  printf("%s\n",fgets(buff,BUFFER_LEN,fp));
  fclose(fp);


}

//child process 2
if(f_id2 == 0 ){
  FILE* fp = fopen("child2.txt", "w" );
  fputs("child2.txt",fp);
  fclose(fp);
  sleep(1);
  char buff[BUFFER_LEN];

  fp = fopen("child2.txt", "r" );
  printf("%s\n",fgets(buff,BUFFER_LEN,fp));
  fclose(fp);
}


}
