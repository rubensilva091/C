#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fd[2][2];
    pipe(fd[0]);

    if(fork() == 0)
    {
        dup2(fd[0][1], 1);
        execlp("grep", "grep", "-v", "^#", "/etc/passwd", NULL);
        close(fd[0][1]);
        _exit(-1);
    }

    close(fd[0][1]);
    wait(NULL);

    pipe(fd[1]);

    if(fork() == 0)
    {

        dup2(fd[0][0], 0);
        close(fd[0][0]);

        dup2(fd[1][1],1);
        close(fd[1][1]);


        execlp("cut", "cut", "-f7", "-d:", NULL);
        _exit(-1);

    }
    close(fd[0][0]);
    close(fd[1][1]);
    wait(NULL);

    pipe(fd[0]);
    if (fork()==0)
    {
        dup2(fd[0][1],1);
        close(fd[0][1]);

        dup2(fd[1][0],0);
        close(fd[1][0]);

        execlp("uniq","uniq",NULL);
        _exit(-1);
    }
    close(fd[0][1]);
    close(fd[1][0]);

    wait(NULL);

    if(fork()==0)
    
    {
        /*Nao posso fazer isto, pois se nao fico sem o output
        dup2(fd[1][1],1);
        close(fd[1][1]);*/

        dup2(fd[0][0],0);
        close(fd[0][0]);

        execlp("wc","wc","-l",NULL);
        _exit(-1);
    }
    close(fd[0][0]);
    wait(NULL);
}