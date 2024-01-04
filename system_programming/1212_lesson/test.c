#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void minus1link(int sig)
{
  printf("to minus 1 link of linkamount.txt\n");
  unlink("./linkamount.txt");
  signal(SIGINT,SIG_DFL);
}

int main()
{
  signal(SIGINT,minus1link);
  int fd = open("./linkamount.txt",O_RDWR|O_CREAT|O_APPEND,0666);
  int fd1 = open("./linkamount.txt",O_RDWR|O_CREAT|O_APPEND,0666);
  write(fd,"Hello world\n",13);
  sleep(60);
  sleep(60);
  write(fd1,"Hello world\n",15);
  sleep(60);
}
