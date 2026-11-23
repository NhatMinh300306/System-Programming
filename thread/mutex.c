#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // for thread
#include <time.h>
// gcc -g -pthread main.c -o main

int mails = 0;

pthread_mutex_t mutex;

// 2 or more processes/threads get access and change a shared variable (variables, files,...) at the same time -> depends of executing order of the process and how the cpu works
// why when i < 100000, mails = 131981 instead of 200000? -> race condition (only on multi-core processor)
// Solve -> mutex: a lock around the section of code
void *routine(void *arg){
    for(int i = 0; i < 10000000; i++){
        pthread_mutex_lock(&mutex);

        mails++;
        
        pthread_mutex_unlock(&mutex);
        // read the value in mails
        // increment the value
        // write mails
    }
}


int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    
    // When create a thread -> it execute a function
    pthread_t t1, t2, t3, t4;

    // Init mutex
    pthread_mutex_init(&mutex, NULL);


    // Initialize threads
    if(pthread_create(&t1, NULL, routine, NULL) != 0){
        return 1;
    }
    if (pthread_create(&t2, NULL, routine, NULL) != 0) {
        return 2;
    }

    if (pthread_create(&t3, NULL, routine, NULL) != 0) {
        return 3;
    }

    if (pthread_create(&t4, NULL, routine, NULL) != 0) {
        return 4;
    }
    // Like in process - wait a thread to finish its execution
    if (pthread_join(t1, NULL) != 0){
        return 5;
    }
    if (pthread_join(t2, NULL)!= 0){
        return 6;
    }    // 'wait', but for thread instead of process

    if (pthread_join(t3, NULL) != 0){
        return 7;
    }

    if (pthread_join(t4, NULL) != 0){
        return 8;
    }


    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);

    return 0;
}