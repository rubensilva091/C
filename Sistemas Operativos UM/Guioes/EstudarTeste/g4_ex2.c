#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int fd_passwd = open("/etc/passwd", O_RDONLY);
    int fd_saida = open("saida.txt", O_CREAT | O_WRONLY, 0666);
    int fd_erros = open("erros.txt", O_CREAT | O_WRONLY, 0666);

    dup2(fd_passwd, 0);
    dup2(fd_saida, 1);
    dup2(fd_erros, 2);
    
    close(fd_passwd);
    close(fd_saida);
    close(fd_erros);

    if (fork() == 0)
    {
        char buffer[512];
        int read_bytes;

        while ((read_bytes = read(0, buffer, 512)) > 0)
        {
            write(1, buffer, read_bytes);
            write(2, buffer, read_bytes);
        }
        _exit(-1);
    }
    else
    {
        wait(NULL);
        printf("\nnoice");
    }
}