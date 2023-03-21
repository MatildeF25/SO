#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int argc, char * argv[]){
    
    pid_t pid = fork();
    int status;

    if(pid ==0){
        execl("/bin/ls", "ls","-l", NULL);
        _exit(4);
    }
    else{
       wait(&status);
       printf("%d\n", WEXITSTATUS(status));
    }
    
    return 0;
}