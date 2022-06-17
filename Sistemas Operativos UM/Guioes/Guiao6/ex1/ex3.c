#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>	/* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int fd_fifo=open("fifo", O_RDONLY);
    char buffer[512];
    int read_bytes;

    while((read_bytes=read(fd_fifo, buffer,512))>0)
    {
        write(1,buffer,read_bytes);
    }
    return 0;
}