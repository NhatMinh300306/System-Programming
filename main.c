#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // for fork()


int main(){
	int id = fork();
	printf("Hello World! - from id: %d\n", id);
	if (id == 0){
		printf("Hello from Child Process\n");
	} else{
		printf("Hello from the Main Process\n");
	}
	return 0;
}
		    

