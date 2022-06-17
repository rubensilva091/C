#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        dup2(fd[1],1);
        execlp("ls", "ls", "/etc", NULL);
        close(fd[1]);
        _exit(-1);
    }
    else
    {
        wait(NULL);
        close(fd[1]);
        dup2(fd[0],0);
        execlp("wc", "wc", "-l", NULL);
        close(fd[0]);
    }
}
