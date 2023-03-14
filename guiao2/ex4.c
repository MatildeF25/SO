#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

    pid_t pid;
    int filho_num, status;

    for(filho_num=1; filho_num<=10;filho_num++){
        
        pid = fork();
        
        if(pid == 0){
            printf("filho - pid: %d\n", getpid());
            printf("filho - pid pai: %d\n", getppid());
            _exit(filho_num);
        }
    }

     for(filho_num; filho_num>1;filho_num--){
        
        pid_t pid_filho = wait(&status);

        if (WIFEXITED(status)!=0){
            printf("Código de saída do filho com pid %d: %d\n" , pid_filho, WEXITSTATUS(status));
        }
        else {
            printf("bad exit\n");
        }
        
    }
    
    return 0;  
}
