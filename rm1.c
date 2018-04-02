#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define SUCCESS 0

void rm1(const char *file) {
    int syscall_return_value = unlink(file);
    if(syscall_return_value != SUCCESS && errno == 21){
		char error_description[256];
		snprintf(error_description, 256, "rm1: cannot remove  \"%s\"", file);
		perror(error_description);	
    }
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("rm0: operand missing\nTry rm --help\n");
	} else{
    	rm1(argv[1]);
	}
}