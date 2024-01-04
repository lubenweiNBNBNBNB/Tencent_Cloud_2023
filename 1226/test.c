#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

static pid_t cid = -2;

void *greeting(void *arg){
  while(cid == -2){sleep(2);}
  printf("Hello world! %s\n",(char *)arg);
}

int main()
{
  pthread_t tid1;
  pthread_create(&tid1,NULL,greeting,"Boys and Girls");

  cid = fork();
  sleep(3);
  pthread_exit(NULL);
  return 0;
}
