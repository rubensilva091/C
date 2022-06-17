#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>
#include <string.h>


/*pid_t getpid(void);
pid_t getppid(void);
pid_t fork(void);
void _exit(int status);
pid_t wait(int *status);
pid_t waitPID(pid_t pid, int *status, int options);
int WIFEXITED(int status); 
int WEXITSTATUS(int status);*/

int main()
{
    int son = getpid();
    int father = getppid();

    char *final;
    int size = snprintf(final,128,"Parent: %d, child: %d", father,son);
    write(1,final,size);
    return 0;
}