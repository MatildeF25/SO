#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>



int mensagem(char* palavra, char* ficheiro) {
    int fd[2];
    pipe(fd);
    int r = 0;

    pid_t pid = fork();

    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        execlp("grep", "grep", palavra, ficheiro, NULL);
        perror("execvp");
        exit(1);
    } else {
        close(fd[1]);
        wait(NULL);

        int fd2[2];
        pipe(fd2);

        pid = fork();
        if (pid == 0) {
            close(fd2[0]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
            dup2(fd2[1], STDOUT_FILENO);
            close(fd2[1]);
            execlp("wc", "wc", "-l", NULL);
            perror("execvp");
            exit(1);
        } else {
            wait(NULL);
            close(fd[0]);
            close(fd2[1]);
            char buffer[10];
            read(fd2[0], buffer, 10);
            r = atoi(buffer);
            close(fd2[0]);
        }
    }

    return r;
}

int autores_que_usaram (char* palavra, int n, char* autores[n]){
    int res = 0;
    int final = 0;
    int fd[2];
    pipe(fd);
    
    for(int i = 0; i<n; i++){
        int r = 0;
        if(fork()==0){
            close(fd[0]);
            if(mensagem(palavra,autores[i])>0){
                r++;
            }
            write(fd[1], &r, sizeof(int));
            close(fd[1]);
            exit(r);
        }
    }
    
    close(fd[1]);
    for (int i = 0; i<n; i++){
        wait(NULL);
        read(fd[0], &res, sizeof(int));
        final += res;
    }
    close(fd[0]);
    return final;
}


int autores_que_usaram2 (char* palavra, int n, char* autores[n]){
    int final = 0;
    int status;

    for(int i = 0; i<n; i++){
        int r = 0;
        if(fork()==0){
            if(mensagem(palavra,autores[i])>0){
                r++;
            }
            exit(r);
        }
    }

    for (int i = 0; i<n; i++){
        wait(&status);
        if(WIFEXITED(status)!=0){
            final += WEXITSTATUS(status);
        }
        
    }

    return final;
}


int main (int argc, char *argv[]){
    
    int n;
    char men[10] = "ola";
    char ficheiro[10] ="in.txt";
    char* autores[2]; // Declare array of char pointers
    
    autores[0] = "afonso.txt"; // Assign the first string
    autores[1] = "joao.txt"; // Assign the second string
    n = mensagem(men,ficheiro);


    int t = autores_que_usaram(men,2,autores);
    perror("deadedad");
    printf("O numero foi: %d\n",n);
    printf("O numero foi: %d\n",t);
    return 0; 
}