#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[]){
    int res;
    int buffer[1024];

    int fd[2];
    pipe(fd);

 
    pid_t pid = fork();
    
    if(pid == 0){
        close(fd[1]);
        dup2(fd[0], 0);

        execlp("wc", "wc", NULL);


        close(fd[0]);
    }
    else{
        close(fd[0]);

        while((res = read(0, buffer, 1024)) > 0){
                write(fd[1], buffer, res);
        }
        
        close(fd[1]);
    
        wait(NULL);
    }
    printf("Terminou\n");
    return 0;
}