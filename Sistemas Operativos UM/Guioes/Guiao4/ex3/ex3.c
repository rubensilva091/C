#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int dup(int fd);
int dup2(int fd1, int fd2);

/*/etc/passwd*/

int main()
{
    execlp("ws","ws",NULL);
}