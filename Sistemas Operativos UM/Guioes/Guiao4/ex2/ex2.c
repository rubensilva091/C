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
    int fd_origem = open("/etc/passwd", O_RDONLY);
    int fd_saida = open("saida.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int fd_error = open("error.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    dup2(fd_origem, 0);
    dup2(fd_saida, 1);
    dup2(fd_error, 2);

    close(fd_origem);
    close(fd_saida);
    close(fd_error);

    int i = fork();
    int bytes_read, stats;
    char buffer[512];

    if (i == 0)
    {
        while ((bytes_read = read(fd_origem, buffer, 512)) > 0)
        {
            write(1, buffer, bytes_read);
            write(2, buffer, bytes_read);
        }
        _exit(-1);
    }
    else
    {
        wait(&stats);
    }
    printf("acabou");
}