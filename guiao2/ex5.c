#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, int* argv[]){
    
    int needle= atoi(argv[1]);
    int row = 10;
    int collumn = 10000;
    int rand_max = 10000;
    int status;
    int **matrix;

    srand(time(NULL));

    matrix = (int**) malloc(sizeof(int*)*row);
    for (int i = 0; i < row; i++){
        matrix[i] = (int*) malloc(sizeof(int)*collumn);
        for (int j = 0; j < collumn ; j++){
            matrix[i][j]= rand() % rand_max;
        }
    }

    for(int k = 0; k<10; k++){
        
        int pid = fork();

        if(pid==0){
            
            printf("pid do filho %d - %d\n", k+1, getpid());
            
            for(int h = 0; h<collumn;h++){
                if(needle==matrix[k][h]){
                    printf("encontrou na linha %d", k+1);
                    _exit(k+1);
                }
            }
            
            _exit(-1);
        }
        
    }

    for(int l = 0; l<10; l++){    
        int pid_filho = wait(&status);

        if(WIFEXITED(status) && WEXITSTATUS(status)!=255){
            printf("O filho com o pid %d encontrou na linha %d\n", pid_filho, WEXITSTATUS(status));
        }

    }

    return 0;

}