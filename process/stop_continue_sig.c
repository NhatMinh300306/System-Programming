#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <unistd.h>


int main(){
    int pid = fork();
    if (pid == -1) {return 1;}

    if (pid == 0){
        while(1){
            printf("Some output\n");
            usleep(50000);
        }
    } else {
        kill(pid, SIGSTOP);
        int t;
        do {
            printf("Time in seconds for execution: ");
            scanf("%d", &t);

            if (t > 0){
                kill(pid, SIGCONT);
                sleep(t);
                kill(pid, SIGSTOP);
            }

        } while(t >0);

        //kill(pid, SIGSTOP); //STOP EXE
        //sleep(1);
        //kill(pid, SIGCONT); //CONTINUE EXE
        //sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }
    return 0;
}