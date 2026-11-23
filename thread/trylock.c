#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>

pthread_mutex_t mutex;

//Trylock: Trying to lock the mutex (waiting, instead of instance like lock)-> always check the return of trylock
// 0 -> lock

void *routine(void *arg){
    (void)arg;
    if(pthread_mutex_trylock(&mutex) == 0){ // EBUSY: != 0
        printf("Got lock\n");
        sleep(1); // this is essential
        pthread_mutex_unlock(&mutex);
        printf("Unlock\n");
    } else{
        printf("Didn't get lock\n");
    }
    return NULL;
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;

    pthread_t th[4];
    for(int i = 0; i < 4; i++){
        if(pthread_create(&th[i], NULL, routine, NULL) != 0){
            perror("Error creating thread");
        }
    }

    for(int i = 0; i < 4; i++){
        if(pthread_join(th[i], NULL) != 0){
            perror("Error joining thread");
        }
    }

    return 0;
}