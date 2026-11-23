#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

// Create 2 Process
// Chile Process generate random numbers -> send them to the parent
// Parent receive -> sum them all


int main(int argc, char *argv[]){
    int fd[2];
    if (pipe(fd) == -1){
        return 2;
    }
    int pid = fork();
    if (pid == -1){
        return 1;
    }

    if (pid == 0){
        // Child Process
        close(fd[0]);
        int n, i;
        int arr[10];
        srand(time(NULL));
        n = rand() % 10 + 1;
        printf("Generated: ");
        for(i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }
        printf("\n");

        if(write(fd[1], &n, sizeof(int)) < 0){
            return 4;
        }
        printf("Send n = %d\n", n);

        if (write(fd[1], arr, sizeof(int) * n) < 0){
            return 3; //error
        }

    } else{
        // Parent process
        close(fd[1]);
        int n, i, sum = 0;
        int arr[10];
        if (read(fd[0], &n, sizeof(int)) < 0) { return 5; }
        printf("Received, n = %d\n", n);

        printf("Received array\n");
        if(read(fd[0], arr, sizeof(int) * 10) < 0){
            return 6;
        }
        for(i = 0; i < n; i++){
            sum += arr[i];
        }

        close(fd[0]);
        printf("Result: %d\n", sum);
        wait(NULL);
    }


    return 0;
}
