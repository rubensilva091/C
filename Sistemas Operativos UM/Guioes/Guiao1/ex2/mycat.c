#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <stdio.h>

#define MAX_BUFFER 512

int main (int argc, char*argv[])
{

    char buffer[MAX_BUFFER];

    /*STDIN pode ser input claramente*/
    printf("%s", argv[1]);

    int bytes_read;

    while((bytes_read=read(0, buffer,MAX_BUFFER))>0)
    {
        write(1, buffer,bytes_read);
    }

}