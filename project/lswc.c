/*
Patrick Punch
2/5/2025
CS 374
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int pfd[2];

    if (pipe(pfd) == -1){
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 == -1){
        perror("fork");
        exit(1);
    }

    if (pid1 == 0){     // ls -1a process
        close(pfd[0]);
        dup2(pfd[1], 1);
        close(pfd[1]);
        execlp("ls", "ls", "-1a", (argc > 1) ? argv[1] : ".", NULL);
        perror("execlp ls process");
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == -1){
        perror("fork");
        exit(1);
    }

    if (pid2 == 0){     // wc -l process
        close(pfd[1]);
        dup2(pfd[0], 0);
        close(pfd[0]);
        execlp("wc", "wc", "-l", NULL);
        perror("execlp wc process");
        exit(1);
    }
    close(pfd[0]);
    close(pfd[1]);

    wait(NULL);
}