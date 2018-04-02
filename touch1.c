#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <utime.h>
#include <time.h>


void touch(const char *file) {
	open(file,O_CREAT, 0664);


	utime(file, NULL);

    
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("rm0: operand missing\nTry touch --help\n");
	}
    touch(argv[1]);
}