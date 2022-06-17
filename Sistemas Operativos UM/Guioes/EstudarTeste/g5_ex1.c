#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    if (fork()==0)
    {
        dup2(fd[1],1);
        close(fd[1]);
        char *buffer="Kinda SUS tbh";
        write(1,buffer,strlen(buffer));
        _exit(-1);
    }
    else
    {
        wait(NULL);

        sleep(5);
        
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        
        char buffer[25];
        int read_bytes;
        while((read_bytes=read(0,buffer,25))>0)
        {
            write(1, buffer,read_bytes);
        }

    }
}