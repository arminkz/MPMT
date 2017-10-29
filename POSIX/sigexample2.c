#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

//
void killHandler(int signum){
  printf("[PID] : %d - KILL INTERRUPT \n",getpid());
  return;
}

//Handles Interrupts on Child Termination (Executes on Parent)
void childHandler(int signum){
  printf("[PID] : %d - CHILD INTERRUPT \n",getpid());
  //Get Child Exit Code
  int status;
  wait(&status);
  int wes = WEXITSTATUS(status);
  printf("[WES] : %d \n",wes);
}

int main() {
  printf("[PID] : %d\n",getpid());

  signal(SIGCHLD,childHandler);
  signal(SIGKILL,killHandler);

  int p = fork();
  if(p==0){
    printf("[PID] : %d - EXITING\n",getpid());
    exit(1);
  }else{
    //Send Kill Signal
    kill(getpid(),SIGKILL);
    wait(NULL);
  }
  return 0;
}
