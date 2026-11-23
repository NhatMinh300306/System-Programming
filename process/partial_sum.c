#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(){
	int arr[] = {3, 2, 1, 4, 2, 1};
	int arrSize = sizeof(arr) / sizeof(int);
	int fd[2];
	int start, end;
	int sum = 0;
	if (pipe(fd) == -1){
		return 1;
	}
	
	int id = fork();
	if (id == -1){
		return 2;
	}

	if (id == 0){ // Child process
		start = 0;
		end = start + arrSize/2;
	} else{
		start = arrSize/2;
		end = arrSize;
	}

	for (int i = start; i < end; i++){
		sum += arr[i];
	}

	printf("Partial sum: %d\n", sum);
	
	if (id == 0){
		close(fd[0]);
		write(fd[1], &sum, sizeof(sum));
		close(fd[1]);
	} else{
		int sumFromChild;
		close(fd[1]);
		read(fd[0], &sumFromChild, sizeof(sumFromChild));
		close(fd[0]);

		int totalSum = sum + sumFromChild;
		printf("Total sum = %d\n", totalSum);
		wait(NULL); // wait for the child to calculate the sum
	}

	return 0;
}
