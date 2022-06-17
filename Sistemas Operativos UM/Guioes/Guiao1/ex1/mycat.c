#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX_BUFFER 512
/*
int open(const char *path, int oflag [, mode]);
ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t write(int fildes, const void *buf, size_t nbyte);
off_t lseek(int fd, off_t offset, int whence);
int close(int fildes);*/

int main(int argc, char *argv[])
{
    char buffer[MAX_BUFFER];
    int fd1 = open("ola.txt", O_RDONLY);
    int fd2 = open("test1.txt", O_WRONLY | O_CREAT, 0666);
    int bytes_read;

    while ((bytes_read = read(fd1, buffer, MAX_BUFFER)) > 0)
    {
        write(fd2, buffer,bytes_read );
    }
    close(fd1);
    close(fd2);
}