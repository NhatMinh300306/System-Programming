#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // for thread
#include <time.h>
// gcc -g -pthread main.c -o main

int mails = 0;

// why when i < 100000, mails = 131981 instead of 200000? -> race condition
// 2 or more processes/threads get access and change a shared variable (variables, files,...) at the same time -> depends of executing order of the process and how the cpu works
void *routine(void *arg){
    for(int i = 0; i < 100000; i++){
        mails++;
        // read the value in mails
        // increment the value
        // write mails
    }
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

    printf("Number of mails: %d\n", mails);

    return 0;
}