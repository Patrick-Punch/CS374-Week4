/*
Patrick Punch
2/5/2025
CS 374
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 3){
        fprintf(stderr, "usage: ./redirout filename command ...\n");
        return 1;
    }

    int fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1){
        perror("open");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1){
        perror("dup2");
        close(fd);
        return 1;
    }
    close(fd);

    if (execvp(argv[2], &argv[2]) == -1){
        perror("Error handling execvp");
    }
    return 1;
}