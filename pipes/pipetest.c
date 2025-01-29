/*
Patrick Punch
1/27/2025
CS 374
*/
#include <stdio.h>
#include <unistd.h>

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
    printf("%d\n%d\n", pfd[0], pfd[1]); // fd 0, 1, and 2 are taken by default

    ssize_t count = write(pfd[1], "Hello\n", 6);
    if (count == -1){
        perror("write");
        return 2;
    }
    ssize_t bytes = read(pfd[0], buf, 128);
    if (bytes == -1){
        perror("read");
        return 3;
    }

    printf("Wrote %zd bytes\n", count);
    write(1, buf, bytes);
    close(pfd[0]);
    close(pfd[1]);
}