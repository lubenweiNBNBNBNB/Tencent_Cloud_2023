#include<sys/types.h>
#include<stdio.h>

int main()
{
  int remaining = 4;
  int child_pid;

  while(remaining > 0)
  {
    child_pid = fork();
    if(child_pid == 0) break;
    remaining--;
  }
  printf("P");
  wait();
  return 0;
}

