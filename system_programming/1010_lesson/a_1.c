#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <signal.h>  

int main(int argc, char *argv[]) {  
    
    //打印进程pid，进程组组长pgid
    printf("I am a_1.out, pid=%d, pgid=%d\n",getpid(),getpgrp());
    system("echo 1");
    sleep(2);
    printf("\n");
    printf("*");
    return 0;  
}
