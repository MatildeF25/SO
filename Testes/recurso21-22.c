#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


int comando (const char* filtro, const char* entrada, const char* saida){
    int fd[2];
    pipe(fd);

    int in = open(entrada, O_RDONLY);
    if(in ==-1){
        perror("in");
        return -1;
    }
    
    int out = open(saida, O_WRONLY);
    if(out == -1){
        perror("out");
        return -1;
    }

    if(fork()==0){
        close(fd[0]);
        dup2(in,0);
        close(in);
        dup2(out,1);
        close(out);
        dup2(fd[1],stderr);
        close(fd[1]);
        execlp(filtro, filtro, NULL);
        perror("exec");
        exit(1);
    }
    else{
        wait(NULL);
        close(fd[1]);
        char buffer[1060];
        size_t bytes;
        if(bytes = read(fd[0], buffer, 1060) > 0){
            return 1;
        }
    }

    return 0;
}


void servidor (){
    mkfifo("fifo", 0666);
    int r = open("fifo", O_RDONLY);
    int w = open("fifo", O_WRONLY);
    int status;
    size_t bytes;
    char buffer[1064];
    int i = 0;
    char *comandos[5];
    
    while (bytes = read(r, buffer, 20)){
        if(i<5){
            comandos[i] = buffer;
            i++;
        }
        else{
            for(int j = 0; j<5; j++){
                if(fork()==0){
                    char *filtro = strsep(comandos[j]," ");
                    char *entrada = strsep(comandos[j]," ");
                    char *saida = strsep(comandos[j],"\0");

                    int e = comando(filtro,entrada,saida);
                    if(e==1){
                        exit(j);
                    }
                    else{
                        exit(10);
                    }
                }
            }
            for(int j = 0; j<5; j++){
                wait(&status);
                if(WIFEXITED(status)!=0){
                    if(WEXITSTATUS(status)<5){
                        int fd = open("comandos.log", O_WRONLY | O_APPEND);
                        write(fd,comandos[j],20);
                        close(fd);
                    }
                }
            }
            i=0;
        }
    }
    close(r);
    unlink("fifo");
}


int main (int argc, char* argv[]){
    if(argc < 4){
        printf("Usage: %s <filtro> <entrada> <saida>\n", argv[0]);
        return 1;
    }

    int res = comando(argv[1], argv[2], argv[3]);
    if(res == 1){
        printf("Ocorreu um erro\n");
        return 1;
    }
    else if(res == -1){
        printf("Ocorreu um erro\n");
        return 1;
    }
    else{
        printf("Sucesso\n");
        return 0;
    }
}