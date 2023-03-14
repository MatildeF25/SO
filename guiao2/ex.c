#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
    printf("pid: %d \n", getpid());
    printf("pai pid: %d \n ", getppid());   
    //sleep(10);
}

























