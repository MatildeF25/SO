#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[]){
    if(makefifo("fifo", 0666) == -1){
        perror("error fifo");
    }
    return 0;
}



