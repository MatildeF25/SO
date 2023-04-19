#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>


int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("Erro na abertura do pipe");
        return 1;
    }

    pid = fork();

    if (pid == -1) {
        perror("Erro na criação do processo filho");
        return 1;
    }

    if (pid == 0) {
        close(fd[0]);
        int x = 1;
        int a = 2;
        write(fd[1], &x, sizeof(int));
        printf("Filho escreveu %d no pipe\n", x);

        write(fd[1], &a, sizeof(int));
        printf("Filho escreveu %d no pipe novamente\n", a);
        close(fd[1]);
    } else {
        close(fd[1]);
        int z;
        while(read(fd[0], &z, sizeof(int)) > 0){
            printf("Pai leu %d do pipe\n", z);
        }
        printf("EOF no descritor de leitura do pai.\n");
        wait(NULL);
        close(fd[0]);
    }

    return 0;
}