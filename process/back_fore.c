#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// Handling Signal -> Prevent the process being sent to the background

void handle_sigtstp(int sig){
    printf("Stop not allowed\n");
}

int main(){
    //struct sigaction sa; //sigaction: how to handle signal
    //sa.sa_handler = &handle_sigtstp;// Funtion pointer //SIGTSTP: terminal stop (CTRL + Z)
    //sa.sa_flags = SA_RESTART;
    //sigaction(SIGTSTP, &sa, NULL);

    signal(SIGTSTP, &handle_sigtstp);
    

    int x;
    printf("Input a number: ");
    scanf("%d", &x);
    printf("Result %d * 5 = %d\n", x, x * 5);

    return 0;
}