#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Execute the command using this shell program.  */
int main (int argc, char *argv[])
{
  if(argc!=2){
    printf("%s\n","please pass in a process as an argument");
    return 0;
  }
  char SHELL[1024];
  getcwd(SHELL, sizeof(SHELL));


  char* command = argv[1];
  strcat(SHELL,"/");

  strcat(SHELL,command);

  int status;
  pid_t pid;


  pid = fork ();
  if (pid == 0)
    {
      printf("full path: %s %s\n",SHELL,command);
      /* This is the child process.  Execute the shell command. */
      execl (SHELL,command, NULL);
      _exit (EXIT_FAILURE);
    }
  else if (pid < 0)
    /* The fork failed.  Report failure.  */
    status = -1;
  else
  sleep(5);
  kill (0, SIGINT);
  printf("%s\n","woke up");
    /* This is the parent process.  Wait for the child to complete.  */
    if (waitpid (pid, &status, 0) != pid)
      status = -1;
  return status;
}
