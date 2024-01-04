#include<stdio.h>
#include<fcntl.h>
int main(int argc, char*argv[])
{
  int fdl;
  char c1,c2;
  char *fname = argv[1];
  fdl = open(fname,O_RDONLY,0);
  read(fdl,&c1,1);
  if(fork()){
    read(fdl,&c2,1);
    printf("Parent: c1 = %c, c2 = %c\n",c1,c2);
  }
  else{
    sleep(5);
    read(fdl,&c2,1);
    printf("Child: c1 = %c, c2 = %c\n",c1,c2);
  }
  return 0;
}
