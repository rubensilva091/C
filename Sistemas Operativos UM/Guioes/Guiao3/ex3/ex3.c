#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
/*int execl(const char *path, const char *arg0, ..., NULL);
int execlp(const char *file, const char *arg0, ..., NULL);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);*/

int main(int argc, char *argv[])
{

    pid_t j;
    int status;

    for (int i=1; argv[i];i++)
    {
        int id;
        if((id=fork())==0)
        {
            execvp(argv[i],argv[i]);
            _exit(-1);
        }
    }

    for (int i=1;argv[i];i++)
    {
        j=wait(&status);
        if (WEXITSTATUS(status)==255)
        {
            printf("jordiiinha");
        }
        else
        {
            printf("funcionou");
        }
    }
}