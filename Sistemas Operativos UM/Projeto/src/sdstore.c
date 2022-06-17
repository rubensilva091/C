#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX 1024

char isnum(char c)
{
    if (c >= '0' && c <= '9')
        return 1;

    return 0;
}

char **gargv;
char *final;
int pid;

char *bytes_files(char *file1, char *file2)
{
    char *buff1 = malloc(sizeof(int) * 100);
    char *buff2 = malloc(sizeof(int) * 100);
    char *prog = malloc(sizeof(int) * 100);

    int fd1[2];
    if (pipe(fd1) == -1)
    {
        perror("error in pipe 1\n");
        exit(1);
    }

    int pid1 = fork();
    if (pid1 == -1)
    {
        perror("error in fork 1\n");
        exit(1);
    }

    if (pid1 == 0)
    {
        close(fd1[0]);
        dup2(fd1[1], STDOUT_FILENO);
        close(fd1[1]);
        execlp("wc", "wc", "-c", file1, NULL);
        perror("exec 1");
        exit(1);
    }
    waitpid(pid1, NULL, 0);
    close(fd1[1]);

    int fd2[2];
    if (pipe(fd2) == -1)
    {
        perror("error in pipe 2\n");
        exit(1);
    }

    int pid2 = fork();
    if (pid2 == -1)
    {
        perror("error in fork 2\n");
        exit(1);
    }
    
    if (pid2 == 0)
    {
        close(fd2[0]);
        dup2(fd2[1], STDOUT_FILENO);
        close(fd2[1]);
        execlp("wc", "wc", "-c", file2, NULL);
        perror("exec 1");
        exit(1);
    }
    waitpid(pid2, NULL, 0);
    close(fd2[1]);

    int next_pos = 0;

    while (next_pos < 100 && read(fd1[0], buff1 + next_pos, 1) > 0)
    {

        if (isnum(buff1[next_pos]))
        {
            next_pos++;
        }
        else
        {
            next_pos = 0;
            break;
        }
    }
    while (next_pos < 100 && read(fd2[0], buff2 + next_pos, 1) > 0)
    {

        if (isnum(buff2[next_pos]))
        {
            next_pos++;
        }
        else
        {
            break;
        }
    }

    sprintf(prog, "Concluded (bytes-input: %s, bytes-output: %s)\n", buff1, buff2);
    free(buff1);
    free(buff2);

    return prog;
}

void sigusr1(int signum)
{
    write(1, "Pending\n", strlen("Pending\n"));
}

void sigusr2(int signum)
{
    write(1, "Processing\n", strlen("Processing\n"));
}

void sigchld(int signum)
{
    final = bytes_files(gargv[2], gargv[3]);
    write(1, final, strlen(final));
    exit(1);
}

int main(int argc, char *argv[])
{
    gargv = argv;
    if (signal(SIGUSR1, sigusr1) == SIG_ERR)
    {
        perror("failed sigusr1\n");
        exit(1);
    }

    if (signal(SIGUSR2, sigusr2) == SIG_ERR)
    {
        perror("failed sigusr2\n");
        exit(1);
    }
    if (signal(SIGCHLD, sigchld) == SIG_ERR)
    {
        perror("failed sigchld\n");
        exit(1);
    }

    if (mkfifo("tmp/pipe_exec", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            perror("could not create pipe_exec\n");
            exit(1);
        }
    }
    if (mkfifo("tmp/main_pipe", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            perror("could not create main_pipe\n");
            exit(1);
        }
    }
    if (mkfifo("tmp/pipe_process", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            perror("could not create pipe_process\n");
            exit(1);
        }
    }
    if (mkfifo("tmp/pipe_status", 0777) == -1)
    {
        if (errno != EEXIST)
        {
            perror("could not create pipe_status\n");
            exit(1);
        }
    }

    pid = getpid();

    char *buffer = malloc(sizeof(int) * MAX);

    int fd_exec = open("tmp/pipe_exec", O_WRONLY);
    if (fd_exec < 0)
    {
        perror("Error opening pipe exec");
        exit(1);
    }

    if (argc > 2 && strcmp(argv[1], "proc-file") == 0)
    {
        write(fd_exec, argv[1], 15);
        close(fd_exec);

        int main_pipe = open("tmp/main_pipe", O_WRONLY);

        if (main_pipe == -1)
        {
            perror("Error openning main pipe\n");
        }

        int i = 2;
        char *word = malloc(sizeof(int) * MAX);
        strcpy(word, "");

        while (argv[i])
        {
            strcat(word, argv[i]);
            strcat(word, " ");
            i++;
        }

        if (write(main_pipe, word, strlen(word)) == -1)
        {
            perror("Error writing in main pipe");
            return 2;
        }

        free(word);
        free(buffer);
        close(main_pipe);

        int fd_process = open("tmp/pipe_process", O_WRONLY);
        if (fd_process == -1)
        {
            perror("Error openning process pipe\n");
        }

        char *pid_buffer = malloc(sizeof(char) * 1024);
        sprintf(pid_buffer, "%d", pid);
        write(fd_process, pid_buffer, 1024);
        free(pid_buffer);
        close(fd_process);
    }

    if (argc == 2 && strcmp(argv[1], "status") == 0)
    {
        write(fd_exec, argv[1], strlen(argv[1]));
        close(fd_exec);

        int pipe_status = open("tmp/pipe_status", O_RDONLY);
        if (pipe_status < 0)
        {
            perror("Error opening status pipe");

            return 4;
        }
        int read_bytes = 0;
        char *buf = malloc(sizeof(char) * 1024);

        while ((read_bytes = read(pipe_status, buf, MAX)) > 0)
        {
            write(STDOUT_FILENO, buf, read_bytes);
        }

        free(buf);
        close(pipe_status);

        exit(1);
    }

    while (1);

    return 0;
}
