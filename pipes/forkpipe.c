/*
Patrick Punch
1/27/2025
CS 374
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/*
0 = stdin
1 = stdout
2 = sterr
*/

int main(void)
{
    int pfd[2];
    char buf[128];

    if (pipe(pfd) == -1){
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1){
        perror("fork");
        return 1;
    }
    if (pid == 0){ // Child Process
        close(pfd[0]); // Child won't read from pipe
        char *msg = "Hello, parent!\n";
        write(pfd[1], msg, strlen(msg));
        close(pfd[1]);
    } else { // Parent Process
        close(pfd[1]); 
        ssize_t msg = read(pfd[0], buf, 128); // read the pipe into a buffer
        write(1, buf, msg); // write the buffer to stdout
        close(pfd[0]);
        wait(NULL);
    }
}

/*
pfd[0] -> write, pfd[1] -> read
(parent) pfd[1]↘         ↙ pfd[0] (parent) 
                ━━━━━━━ 
(child) pfd[1]↗         ↖ pfd[0] (child)
*/