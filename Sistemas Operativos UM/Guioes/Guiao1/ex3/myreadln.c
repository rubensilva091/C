#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 512
/*
int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
off_t lseek(int fd, off_t offset, int whence);
int close(int fildes);*/

ssize_t myreadln(int fd, char *line, size_t size)
{
    int bytes_read;


}

int main(int argc, char *argv[])
{
    int fd_origem=open("mytext.txt", O_RDONLY);
    printf("%d",myreadln(fd_origem,argv,MAX_BUFFER));

    return 0;
}