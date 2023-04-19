#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>

int main(){
    int fd[2];

    if(pipe(fd)==-1){
        perror("erro na abertura do pipe\n");
        return 1;
    }

    pid_t pid = fork();

    if(pid == 0){
        close(fd[0]);
        int x = 1;
        write(fd[1], &x, sizeof(int));
        printf("Filho escreveu %d no pipe\n", x);

        int y = 2;
        write(fd[1], &y, sizeof(int));

        printf("Filho escreveu %d no pipe\n", y);
        close(fd[1]);
    }
    else{
        close(fd[1]);
        int z;
        read(fd[0], &z, sizeof(int));
        printf("Pai leu %d do pipe\n", z);

        int w;
        read(fd[0], &w, sizeof(int));
        printf("Pai leu %d do pipe\n", w);

        wait(NULL);
        close(fd[0]);
    }
    return 0;
}