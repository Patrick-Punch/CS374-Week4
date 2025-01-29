/*
Patrick Punch
1/29/2025
CS 374
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("output.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (fd == -1){
        perror("open");
        exit(1);
    }

    int old_stdout = dup(1);

    int pfd = dup2(fd, 1);
    if (pfd == -1){
        perror("dup2");
        close(fd);
        exit(1);
    }

    printf("Hello, world\nThis is a test!\n");
    fflush(stdout);
    
    close(fd);
    dup2(old_stdout, 1);

    printf("All done!\n");
}
