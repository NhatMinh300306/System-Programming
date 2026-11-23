#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// Conditional Variables
pthread_mutex_t mutexFuel;
int fuel = 0;

void *fuel_filling(void *arg){
    (void)arg;
    
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel += 15;
        printf("Filling fuel...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        sleep(1);
    }
    return NULL;
}

void *car(void *arg){
    (void)arg;
    pthread_mutex_lock(&mutexFuel);
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);

    return NULL;
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv; 
    pthread_t th[2];
    pthread_mutex_init(&mutexFuel, NULL);
    for(int i = 0; i < 2; i++){
        if (i == 1){
            if(pthread_create(&th[i], NULL, fuel_filling, NULL) != 0){
                perror("Failed to create thread");
            }
        } else{
            if(pthread_create(&th[i], NULL, car, NULL) != 0){
                perror("Failed to create thread");
            }
        }
    }

    for(int i = 0; i < 2; i++){
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexFuel);

    return 0;
}