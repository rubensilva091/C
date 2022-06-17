#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <stdio.h>



int main(int argc, char *argv[])
{
    int i = fork();
    int parent = getppid();
    int child= getpid();

    char buffer[128];

    int size = snprintf(buffer, 65, "Fork id:%d\nParent id:%d\nChild id:%d\n\n", i,parent,child);
    write(1,buffer,size);
}