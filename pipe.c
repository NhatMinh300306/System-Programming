#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// Communicate between two process (sending, receiving,...)

int main(){
    int fd[2];
    pipe(fd);
    return 0;
}
