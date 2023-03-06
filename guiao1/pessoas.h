#define FILENAME "file_pessoas"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> 

typedef struct Pessoa{
    char name[200];
    int age;
} Pessoa;

int nova_pessoa(char *name, int age);
int muda_idade(char* name, int age);
int muda_idade2(long pos, int age);
 