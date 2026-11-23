#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd[2];
    if(pipe(fd) == -1){
        return 1;
    }

    int pid = fork();
    if (pid < 0) { return 2; }

    if (pid == 0){
        // Child
        close(fd[0]); // close read
        char str[200];
        printf("Input string: ");
        fgets(str, 200, stdin); // At the end of the string, there will be '\0'
        str[strlen(str) - 1] = '\0';

        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) < 0){
            return 4;
        }

        if(write(fd[1], str, strlen(str) + 1) < 0) {
            return 3;
        }

        close(fd[1]);


    } else{
        // Parent
        close(fd[1]); // close write
        char str[200];
        int n;
        if (read(fd[0], &n, sizeof(int)) < 0){
            return 5;
        }
        if (read(fd[0], str, sizeof(char) * n) < 0){
            return 6;
        }

        close(fd[0]);
        printf("Received: %s\n", str);
    }
    return 0;   
}