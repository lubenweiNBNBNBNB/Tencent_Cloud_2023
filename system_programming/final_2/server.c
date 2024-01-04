#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/select.h>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

#define FIFO_NAME1 "/home/wangyaxian2022150054/5_final_assignment/wyx_register"
#define FIFO_NAME2 "/home/wangyaxian2022150054/5_final_assignment/wyx_login"
#define FIFO_NAME3 "/home/wangyaxian2022150054/5_final_assignment/wyx_sendmsg"
#define FIFO_NAME4 "/home/wangyaxian2022150054/5_final_assignment/wyx_logout"
//#define LOG_TXT "/var/log/chat-logs/LOGFILES"
#define LOG_TXT "/home/wyx/system_programming/final_2/LOGFILES"

char buffer[50];

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0) {  perror("Fork failed");exit(1);}

    // 父进程退出
    if (pid > 0) {  exit(0); }
    // 子进程继续执行
    printf("child is working\n");

//建立日志文件
    int file = open(LOG_TXT,O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(file == -1) 
    {   
        printf("Failed to open file\n");
        exit(0);
    }   

    // 重定向标准输入、输出和错误流到 /dev/null
   // open("/dev/null", O_RDONLY);
   // open("/dev/null", O_WRONLY);
   // open("/dev/null", O_WRONLY);
    freopen("/dev/null", "r", stdin);
    //freopen("/dev/null", "w", stdout);
    freopen(LOG_TXT, "w", stdout);
    //freopen("/dev/null", "w", stderr);
    freopen(LOG_TXT, "w", stderr);
   // if(dup2(file,STDOUT_FILENO) == -1)
   // {
   //     printf("Failed to redirect stdout\n");
   //     exit(0);
   // }

    printf("\nServer is rarin' to go!\n");
    fflush(NULL);

    while(1)
    {
        printf("\nServer is rarin' to go!\n");
        sleep(1);
        fflush(NULL);
    }
    return 0;
}