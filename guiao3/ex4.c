#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int mySystem(char *string) {
    int i = 0;
    int status;
    char *copy = strdup(string);
    char *token, *word[20];

    while ((token = strsep(&copy, " ")) != NULL && i < 19) {
        word[i] = strdup(token);
        i++;
    }
    
    word[i] = NULL; 

    pid_t pid = fork();

    if (pid == 0) {
        execvp(word[0], word);
        _exit(4);
    }

    wait(&status);

    for (i = 0; word[i] != NULL; i++) {
        free(word[i]); 
    }

    free(copy); 
    return 0;
}

int main(int argc, char* argv[]){

    char comando1[] = "ls -l -a -h";
    char comando2[] = "sleep 10";
    char comando3[] = "ps";

    mySystem(comando3);
}