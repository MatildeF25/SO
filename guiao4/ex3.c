#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
    int fd[2];

    if(pipe(fd) == -1){
        perror("erro a abrir pipe");
        return 1;
    }

    pid_t pid = fork();

    if(pid == 0){
       close(fd[0]);
        int y = 25;
        write(fd[1], &y, sizeof(int));
        printf("Filho escreveu %d no pipe\n", y);
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int x;
        read(fd[0], &x, sizeof(int));
        printf("Pai leu %d do pipe\n", x);
        close(fd[0]);
    }
}