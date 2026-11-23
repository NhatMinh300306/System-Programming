#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    int fd[2]; // for pipe
    if (pipe(fd) == -1){
        printf("Error creating pipe\n");
        return 1;
    }

    int pid = fork();
    if (pid == -1){
        printf("Error creating process\n");
        return 2;
    }

    if (pid == 0){
        // Child process
        // write only - fd[0]: read; fd[1]: write
        close(fd[0]);
        srand(time(NULL));
        int n = rand() % 10 + 1;
        int i;
        int arr[10];
        printf("Generated: ");
        for(i = 0; i < n; i++){
            arr[i] = rand() % 11;
            printf("%d ", arr[i]);
        }

        printf("\n");

        if(write(fd[1], &n, sizeof(int)) < 0){
            printf("Error writing n!\n");
            return 3;
        }

        if (write(fd[1], &arr, sizeof(int) * n) < 0){
            printf("Error writing array!\n");
            return 4;
        }

    } else{
        // Parent process
        // Read only
        close(fd[1]);
        int n;
        int arr[10];

        if (read(fd[0], &n, sizeof(int)) < 0){
            printf("Error reading n!\n");
            return 6;
        }

        if (read(fd[0], &arr, sizeof(int) * 10) < 0){
            printf("Error reading arr!\n");
            return 7;
        }

        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += arr[i];
        }

        float avg = (float)sum / n;

        printf("Avg = %.2f\n", avg);
        
        wait(NULL);
    }

    close(fd[0]);
    close(fd[1]);
    return 0;
}