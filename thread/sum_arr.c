#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg){
    int index = *(int*)arg;
    int sum = 0;
    for(int i = 0; i < 5; i++){
        sum += primes[index + i];
    }

    *(int*)arg = sum;
    return arg;
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    pthread_t th[10];
    int i;

    for(i = 0; i < 2; i++){
        // Why do we need to allocate memory? -> watch the video
        int *a = (int*)malloc(sizeof(int));
        *a = i * 5;
        if(pthread_create(&th[i], NULL, &routine, a) != 0){
            perror("Failed to create thread");
        }
    }
    int global_sum = 0;
    for(i = 0; i < 2; i++){
        int *arg;
        if(pthread_join(th[i], (void**)&arg) != 0){
            perror("Failed to join thread");
        }
        global_sum += *arg;
        free(arg);
    }
    printf("Global sum: %d\n", global_sum);
    return 0;
} 