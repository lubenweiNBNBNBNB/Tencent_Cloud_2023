#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <signal.h>  
int main(int argc, char *argv[]) {  
    
    
    
    //回显重定向输入
    char ch;
    while((ch=getchar()) != '*')
    {
        putchar(ch);
    }
    printf("\n");
    //打印进程pid，进程组组长pgid
    printf("I am a_2.out, pid=%d, pgid=%d\n",getpid(),getpgrp());
    system("echo 2");
    
    printf("\n");
    printf("*");
    return 0;  
}
