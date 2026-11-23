#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // for thread
#include <time.h>
// gcc -g -pthread main.c -o main

void *routine(void *arg){
    (void)arg; // avoiding waring unused parameter
    printf("Test from threads\n");
    sleep(3);
    printf("Ending thread\n");
    return NULL;
}


int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    
    // When create a thread -> it execute a function
    pthread_t t1, t2;

    // Initialize threads
    if(pthread_create(&t1, NULL, routine, NULL) != 0){
        return 1;
    }
    if (pthread_create(&t2, NULL, routine, NULL) != 0) {
        return 2;
    }
    // Like in process - wait a thread to finish its execution
    if (pthread_join(t1, NULL) != 0){
        return 3;
    }
    if (pthread_join(t2, NULL)!= 0){
        return 4;
    }    // 'wait', but for thread instead of process

    return 0;
}