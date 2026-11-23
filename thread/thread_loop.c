#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // for thread
#include <time.h>
// gcc -g -pthread main.c -o main

int mails = 0;

pthread_mutex_t mutex;


void *routine(void *arg){
    for(int i = 0; i < 100000000; i++){
        pthread_mutex_lock(&mutex);

        mails++;
        
        pthread_mutex_unlock(&mutex);
        
    }
}


int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    
    // When create a thread -> it execute a function
    pthread_t th[4];
    int i;
    // Init mutex
    pthread_mutex_init(&mutex, NULL);

    for(i = 0; i < 4; i++){
        if(pthread_create(th + i, NULL, routine, NULL) != 0){
            return 1;
        }

        printf("Thread %d has started\n", i + 1);

        // If we create and join thread together in a loop -> lost paralellism
        // Ex: thread1 created -> executed -> finished -> thread2->...
        // -> Used two loops

        /*
        if (pthread_join(th[i], NULL) != 0){
            return 2;
        }

        printf("Thread %d has finished\n", i + 1);
        */
    }

    for(i = 0; i < 4; i++){
        if (pthread_join(th[i], NULL) != 0){
            return 2;
        }

        printf("Thread %d has finished\n", i + 1);
    }


    // Initialize threads
   


    pthread_mutex_destroy(&mutex);

    printf("Number of mails: %d\n", mails);

    return 0;
}