#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
int main()
{
  char buf[100]; 
  fd_set my_read; //设置监听集合
  struct timeval tv;//设置等待时间，0不等待，NULL一直等待
  tv.tv_sec = 5; //秒数
  tv.tv_usec = 0;//微秒数，秒后面的零头
  FD_ZERO(&my_read); //清空集合
  /*
  * 通常，一个进程启动时，都会打开 3 个文件：
  * 标准输入（0）、标准输出（1）和标准出错处理 （2）
  */
  /*设置位0为1，将文件描述符0加入集合*/
  FD_SET(0, &my_read);
  int ret;
  while((ret = select(1, &my_read, NULL, NULL, &tv)) == 1) {
  /* data ready on stdin */
    if (FD_ISSET(0, &my_read)){
      fgets(buf, 100, stdin);
      printf("Your input is: %s\n",buf);
    }
    }
    if(ret != 1){
      printf("Your missed your time ...\n");
  }
  return 0;
}

