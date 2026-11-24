#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

// What if we have more than a car that need to be fueled


// Conditional Variables : pthread_cond_wait
pthread_mutex_t mutexFuel;
pthread_cond_t condFuel;
int fuel = 0;

void *fuel_filling(void *arg){
    (void)arg;
    
    for(int i = 0; i < 5; i++){
        pthread_mutex_lock(&mutexFuel);
        fuel += 60;
        printf("Filling fuel...%d\n", fuel);
        pthread_mutex_unlock(&mutexFuel);
        //pthread_cond_signal(&condFuel); // signal 1 thread to wake up
        pthread_cond_broadcast(&condFuel); // signal all threads to wake up
        sleep(1);
    }
    return NULL;
}

void *car(void *arg){
    (void)arg;
    pthread_mutex_lock(&mutexFuel);
    while (fuel < 40){
        printf("No fuel. Waiting...\n");
        //sleep(1);
        pthread_cond_wait(&condFuel, &mutexFuel);
    }
    fuel -= 40;
    printf("Got fuel. Now left: %d\n", fuel);
    pthread_mutex_unlock(&mutexFuel);

    return NULL;
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv; 
    pthread_t th[5];
    pthread_mutex_init(&mutexFuel, NULL);

    //Init conditional variable.
    pthread_cond_init(&condFuel, NULL);

    for(int i = 0; i < 5; i++){
        if (i == 4){
            if(pthread_create(&th[i], NULL, fuel_filling, NULL) != 0){
                perror("Failed to create thread");
            }
        } else{
            if(pthread_create(&th[i], NULL, car, NULL) != 0){
                perror("Failed to create thread");
            }
        }
    }

    for(int i = 0; i < 5; i++){
        if (pthread_join(th[i], NULL) != 0){
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexFuel);
    pthread_cond_destroy(&condFuel);
    return 0;
}