#include <unistd.h>
#include <sys/wait.h>
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]){

    int result[100];

    int fd[2];
    pipe(fd);

    int needle= 5;
    int row = 10;
    int collumn = 10000;
    int rand_max = 10000;
    int status;
    int **matrix;
    int arraypid[11];

    srand(time(NULL));

    matrix = (int **) malloc(sizeof(int*)*row);
    for (int i = 0; i < row; i++){
        matrix[i] = (int*) malloc(sizeof(int)*collumn);
        for (int j = 0; j < collumn ; j++){
            matrix[i][j]= rand() % rand_max;
        }
    }

    int k = 0;
    int iarray = 0;
    pid_t pidF;

    while(k<row){
        if((pidF = fork()) == 0){
            close(fd[0]);
        
            int num=0;
            printf("%d:O meu F_PID = %d P_PID = %d\n",k,getpid(),getppid());
            for(int c=0; c<collumn; c++){
                if(matrix[k][c] == needle) num++;
            }

            write(fd[1],&num,sizeof(num));
            _exit(k);

        }else{
            arraypid[iarray] = pidF;
            iarray++;
        }
        
        k++;
    }

    close(fd[1]);
    iarray = 0;
    k=0;
    int res = 0;
    
    while(k<row){

        pid_t terminated_pid = waitpid(arraypid[iarray],&status,0);
        read(fd[0],&res,sizeof(int));
        result[k]= res;
        res=0;
        if (WIFEXITED(status))
        {

            printf("Pai: recebi a linha %d para o pid %d\n", WEXITSTATUS(status), terminated_pid);
            printf("Numero de ocorrecias do %d na linha %d: %d\n",needle, WEXITSTATUS(status),result[k]);
            printf("\n");
        }
        else
        {
            printf("erro\n");
        }
        k++;
        iarray++;
    }

    return 0;

}