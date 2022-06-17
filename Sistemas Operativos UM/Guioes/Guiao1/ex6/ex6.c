#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 512
/*
int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
off_t lseek(int fd, off_t offset, int whence);
int close(int fildes);*/

typedef struct Person
{
    char *nome;
    int idade;
    float salary;
} Person;

int selector(char *c, Person pessoa, int fd)
{
    if (!strcmp(c, "-i"))
    {
        int bytes_read;
        char buffer[MAX_BUFFER];

        while((bytes_read=read(fd,buffer,MAX_BUFFER))>0)
        {

        }
        return 1;
    }
    else if (!strcmp(c, "-u"))
    {
        printf("-u");
        return 2;
    }
    else
    {
        printf("ERROR, Comando nao existe");
        return -1;
    }
}

int write_pessoas(char *nome)
{

}

int main(int argc, char *argv[])
{
    Person pessoa;
    pessoa.nome=argv[2];
    pessoa.idade=argv[3];

    int fd = open("file.txt", O_RDWR | O_WRONLY | O_TRUNC | O_CREAT, 0666);
    selector(argv[1], pessoa,fd);
}