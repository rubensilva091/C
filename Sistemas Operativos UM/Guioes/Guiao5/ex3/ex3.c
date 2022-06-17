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

    if (fork()!=0)
    {

        /*Processo pai*/
        int bytes_read;
        char buffer[512];
        close(fd[0]);
        while((bytes_read=read(0,buffer,512))>0)
        {
            write(fd[1],buffer,bytes_read);
        }
        close(fd[1]);
        wait(NULL);
        printf("ACABOU");

    }
    else
    {
        /*Processo Filho*/
        close(fd[1]);
        dup2(fd[0],0);
        execlp("ws","ws",NULL);
        close(fd[0]);
        _exit(-1);

    }
}