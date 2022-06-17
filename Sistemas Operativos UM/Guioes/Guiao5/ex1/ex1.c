#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>	/* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>


int main()
{
    int fd[2];

    pipe(fd);

    int i =fork();

    if (i==0)
    {
        close(fd[0]);
        char *c ="Questa merda";
        write(fd[1], c, sizeof(c));
        close(fd[1]);
        _exit(-1);
    }
    else
    {

        wait(NULL);
        sleep(5);
        int bytes_read;
        char c[512];
        close(fd[1]);
        while((bytes_read=read(fd[0],c,512))>0)
        {
            write(1,c,bytes_read);
        }
        close(fd[0]);
    }
}