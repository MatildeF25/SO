#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    pid_t pid;
    int status;

    if((pid = fork()) == 0){
        printf("filho - pid: %d\n", getpid());
        printf("filho - pid pai: %d\n", getppid());
        _exit(0);
    }
    
    else{
        printf("pai - pid: %d\n", getpid());
        printf("pai - pid pai: %d\n", getppid());

        if(wait(&status)>0){
            
    }if (WIFEXITED(status)){
                printf("exit value %d\n" , WEXITSTATUS(status));
            }
            else {
                printf("bad exit\n");
            }
        }
        printf("parent is exiting...\n");
    return 0;
}
