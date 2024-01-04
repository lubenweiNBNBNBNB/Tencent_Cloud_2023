#include<stdio.h>
#include<unistd.h>

int main()
{
  for(int i=0;i<3;i++)
  {
    fork();
    //printf("*\n";
    printf("*");
  }
  return 0;
}
