#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int vacinados(char* regiao, int idade) {
    char idade_char[10];
    snprintf(idade_char, 10, " %d ", idade);
    int re = 0;
    int fd1[2];
   
    pipe(fd1);
    

    if (fork() == 0) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);
        execlp("grep", "grep", idade_char, regiao, NULL);
        perror("grep");
        exit(1);
    } else {
        close(fd1[1]);
        int fd2[2];
        pipe(fd2);
        
        if (fork() == 0) {
            close(fd1[1]);
            close(fd2[0]);
            dup2(fd1[0], 0);
            close(fd1[0]);
            dup2(fd2[1], 1);
            close(fd2[1]);
            execlp("wc", "wc", "-l", NULL);
            perror("wc");
            exit(1);
        } else {
            wait(NULL);
            wait(NULL);
            close(fd1[0]);
            close(fd2[1]);
            char res[10];
            read(fd2[0], res, 10);
            re = atoi(res);
            close(fd2[0]);
        }
    }
    return re;
}





int main (int argc, char *argv[]){
    int res = vacinados("in.txt", 55);
    printf("R -> %d\n", res);
    return 0;
}




int main (int argc, char *argv[]){
    
    mkfifo("fifo",0666);
    int r = open("fifo", O_RDONLY);
    int w = open("fifo", O_WRONLY);
    ssize_t bytes;
    char buffer[14];

    while (bytes = read(r, buffer, 14)>0){
        char reg[10];
        snprintf(reg, "%c.txt", buffer[12]);

        int fd_fich = open(reg, O_CREAT | O_APPEND | O_WRONLY);
        write(fd_fich,buffer,14);
        write(fd_fich, "\n",1);

        close(fd_fich);
    }
    
    close(r);
    unlink("fifo");
    return 0;
} 
