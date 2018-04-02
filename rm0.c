#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>


void rm0(const char *file) {
    unlink(file);
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("rm0: operand missing\nTry rm --help\n");
	}
    rm0(argv[1]);
}