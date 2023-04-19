#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main (int argc, char * argv[]){

    int status;

    for(int i = 0; i<argc; i++){
        
        pid_t pid = fork();

        if(pid==0){
            execlp(argv[i+1],NULL);
            _exit(4);
        }

    }

    for(int i = 0; i<argc; i++){
        wait(&status);
    }
        
    return 0;
}
