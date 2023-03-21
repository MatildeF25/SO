#include <unistd.h>


int main (int argc, char * argv[]){
    
    execl("/bin/ls", "ls","-l", NULL);
    
    return 0;
}