#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
    int fd[2];
    
    if (pipe(fd) == -1){
        perror("erro a abrir o pipe"); // erro a abrir o pipe
        return 1; 
    }

    pid_t pid;

    pid = fork();
    
    if(pid == 0){
        close(fd[1]);
        int x;
        read(fd[0], &x, sizeof(int));
        printf("Filho leu %d do pipe\n", x);
        close(fd[0]);
    }
    else{
        close(fd[0]);
        int y = 42;
        write(fd[1], &y, sizeof(int));
        printf("Pai escreveu %d no pipe\n", y);
        close(fd[1]);
        wait(NULL);
    }

    return 0;
}