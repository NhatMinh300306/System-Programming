#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>

// How to get a value (from thread) at main

void *roll_dice(void *arg){
    (void)arg;

    int *value = (int*)malloc(sizeof(int));
    if (value == NULL){
        return NULL;
    }

    *value = rand() % 6 + 1;
    printf("%d\n", *value);



    return (void*)value;
}

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    int *res;
    srand(time(NULL));

    pthread_t th;
    if (pthread_create(&th, NULL, roll_dice, NULL) != 0){
        return 1;
    }


    // Return value here
    if (pthread_join(th, (void**)&res) != 0){
        return 2;
    }

    printf("Result is: %d\n", *res);
    free(res);
    return 0;
}