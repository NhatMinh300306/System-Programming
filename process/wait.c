#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <sys/wait.h>

// wait: stop execution until a child process finish its execution -> wait for a child process

int main(int argc, char *argv[]){
    int id = fork(); // THe programe will continue to execute the command after fork()
    int n;
    if (id == 0){ // Child Process
        n = 1;
    } else{
        n = 6;
    }

    if (id != 0){
        wait(NULL);
    }
    int i;
    for (i = n; i < n + 5; i++){
        printf("%d ", i);
        fflush(stdout);
    }

    if (id != 0){
        printf("\n");
    }



    return 0;
}
