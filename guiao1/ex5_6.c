#include "pessoas.h"

int nova_pessoa(char *name, int age){

    int res;
    Pessoa p;
    p.age = age;
    
    snprintf(p.name, 200, "%s", name);

    int fd = open(FILENAME, O_WRONLY, 0640);

    if(fd < 0){
        write(1, "erro", 4);
    }
    
    res = write(fd, &p, sizeof(Pessoa));

    return res;
}


int muda_idade(char* name, int age){
    Pessoa p;
    int res;
    int bytes_read;

    int fd = open(FILENAME, O_WRONLY, 0640);

    if(fd < 0){
        write(1, "erro", 4);
    }

    while((bytes_read = read(fd, &p, sizeof(Pessoa)))>0){

    
        if(strcmp(p.name,name)){
            p.age = age;

            res = lseek(fd, sizeof(Pessoa), SEEK_CUR);

        }
    
        if(res<0){
            perror("erro");
            return -1;
        }

        res = write(fd, &p, sizeof(Pessoa));
        
    
    }
}