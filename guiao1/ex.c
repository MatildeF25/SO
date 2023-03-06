#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
    
int mycp(char const * from_path, char const * to_path){
    
    int from_fd = open(from_path, O_RDONLY, 0640); // abrir o ficheiro 

    if(from_fd < 0){
        write(1, "erro", 4);
    }

    // ver se o ficheiro out existe se existir limpar o ficheiro se não existir criar o ficheiro
    int to_fd = open(to_path, O_CREAT | O_TRUNC | O_WRONLY, 0640);
   
    if(to_fd < 0){
        write(1, "erro", 4);
    }
    
    int read_bytes = 0;
    char buf[1024];

    while((read_bytes = read(from_fd,buf,1024))>0){ 
        write(to_fd, buf, read_bytes);
    }

    close(from_fd);
    close(to_fd);

    return 0;
}

int mycat(){
    
    int read_bytes = 0;
    char buf[1024];

    while((read_bytes = read(0,buf,1024))>0){ // lê dados do terminal STDIN
        write(1, buf, read_bytes); // escreve dados no terminal
    }

    return 0;
}

ssize_t readLine(int fd, char *line, size_t size){
    
    int read_bytes = 0;
    char buf[1];
    

    while((read(fd,buf,1))>0 && (read_bytes < size - 1)){ 
        if(buf[0] == '\n'){
            line[read_bytes] = buf[0];
            read_bytes++;
            line[read_bytes]='\0'; 
            return read_bytes;
        }
        else{
            line[read_bytes] = buf[0];
            read_bytes++;
        }

        
    }
    
    line[read_bytes] = '\0';
    return read_bytes; 
}

int mynl(char const * from_path){
        
    int from_fd = open(from_path, O_RDONLY, 0640); // abrir o ficheiro 

    if(from_fd < 0){
        write(1, "erro", 4);
    }
    
    int num_line = 1;
    char num_str[4];
    int read_bytes = 0;
    char buf[1024];
    char* line = malloc(sizeof(char) * 1024); // allocate memory for line

    while ((read_bytes = readLine(from_fd, line, 1024)) > 0) {
        snprintf(num_str, 4, "%d:", num_line);
        write(1, num_str, strlen(num_str));
        write(1, " ", 1);
        write(1, line, read_bytes);
        num_line++; 
    }

    free(line);
    close(from_fd);
    return 0;
}






// ./mycp from.txt to.txt 

int main (int argc, char const * argv[]){

    //return mycp(argv[1], argv[2]);
    //return mycat();
    return mynl(argv[1]);
}