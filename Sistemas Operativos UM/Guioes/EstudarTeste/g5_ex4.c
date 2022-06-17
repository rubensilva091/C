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

    char buffer[1];
    if(fork()==0)
    {

        dup2(fd[1],1);
        close(fd[1]);
        execlp("ls","ls","/etc",NULL);
        _exit(-1);
    }
    else
    {
        wait(NULL);
        printf("Processo Filho 1 Terminado");
    }
    close(fd[1]);

    if(fork()==0)
    {   
        close(fd[1]);
        dup2(fd[0],0);
        close(fd[0]);
        execlp("wc", "wc", "-l", NULL);
        _exit(-1);
    }
    else
    {
        wait(NULL);
        printf("\nProcesso Filho 2 terminado");
    }


}