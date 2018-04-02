#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("ln0: operand missing\nTry ln --help\n");
	}else{
		symlink(argv[1], argv[2]);
	}
}