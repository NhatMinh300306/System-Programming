#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(){
	int pid = fork();
	if (pid == -1){
		return 1; //exit(1)
	}

	if (pid == 0){
		// child process
		int file = open("ping_res.txt", O_WRONLY | O_CREAT, 0777);
		if (file == -1){
			return 2;
		}
		
		printf("The fd to ping_res: %d\n", file);

		int file2 = dup2(file, STDOUT_FILENO); // return another file descriptor for ping_res
		printf("The duplicatid fd: %d\n", file2);
		close(file);


	        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1){
			printf("Couldn't execute!\n");
			return 0;
		}
	} else{
		int wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus)){
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0){
				printf("Success!\n");
			} else{
				printf("Failure - Status Code: %d\n", statusCode);
			}
		}
		
		printf("Success\n");
	}

	//execlp("ping", "ping", "-c", "3", "google.com", NULL);
	//printf("Success!\n"); // this will not be printed
	

	// In linux, exit code != 0 -> error
	return 0;

}
