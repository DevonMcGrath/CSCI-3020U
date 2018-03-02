/*

- The parent process must check the return status of the child process after
it has finished waiting.
- See the following for more information on forking and waiting:
http://www.cs.rutgers.edu/~pxk/416/notes/c-tutorials/
*/

#define _XOPEN_SOURCE 700 // required for barriers to work
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
int main(void)
{

pid_t fid1 = fork();
int status;

if(fid1==0){
  sleep(1);
  printf("%s\n","Child process");
  exit(0);
}
wait(&status);

printf("%s\n","Parent process");
printf("status: %d\n",status);





}
