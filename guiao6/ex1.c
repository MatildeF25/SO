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
    int buffer[100];
    
    int fdin = dup(0);
    int fdout = dup(1);
    int fderr = dup(2);

    int fd_pass = open("/etc/passwd", O_RDONLY);
    int fd_saida = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int fd_erro = open("erro.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    dup2(fd_pass, 0);
    close(fd_pass);

    dup2(fd_saida, 1);
    close(fd_saida);

    dup2(fd_erro, 2);
    close(fd_erro);

    while((res = read(0, buffer, 100)) > 0){
        write(1, buffer, res);
        write(2, buffer, res);
        printf("ola\n");
        fflush(stdout);
    }

    
    dup2(fdin, 0);
    close(fdin);
    dup2(fdout, 1);
    close(fdout);
    dup2(fderr, 2);
    close(fderr);

    printf("Terminou\n");
    return 0;
}