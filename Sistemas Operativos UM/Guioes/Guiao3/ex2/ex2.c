#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
/*int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);*/

int main()
{
    pid_t pid;
    int status;

    int i = fork();
    if (i == 0)
    {
        execlp("/bin/ls", "ls", NULL);
        _exit(-1);
    }
    else
    {
        pid = wait(&status);

        char *c = "Processo PAI, nada a ver aqui\n";
        write(1, c, (strlen(c)));
    }
}