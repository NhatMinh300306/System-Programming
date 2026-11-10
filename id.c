#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main(){
    int id = fork();

    // Orphan process
    if (id == 0){
        sleep(1);
    }
    printf("Current ID: %d, Parent ID: %d, id = %d\n", getpid(), getppid(), id);

    int res = wait(NULL); // process id you are actually wait for
    if (res == -1){
        printf("No children to wait for\n");
    } else{
        printf("%d finished execution - %d id\n", res, id);
    }
    return 0;
}
