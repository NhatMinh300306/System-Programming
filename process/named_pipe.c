#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <fcntl.h> // file control -> open()

// FIFOs: a type of file -> read/write from any process
// aka named pipes
//
// Opening the read/write end of a FIFO BLOCKS until the other end is also opened (by another process/thread)
int main(){
	if(mkfifo("myfifo1", 0777) == -1){
		if (errno != EEXIST){
			printf("Couldn't create fifo file\n");
			return 1;
		}
	}
        printf("Opening...\n");
	int fd = open("myfifo1", O_WRONLY);
	printf("Opened\n");
	int x = 67;
	if(write(fd, &x, sizeof(x)) == -1){
		return 2;
	}
	printf("Written\n");

	printf("Closed\n");
	close(fd);
	

	return 0;
}
