#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>


#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("mv0: operand missing\nTry ln --help\n");
	}else{
		rename(argv[1], argv[2]);
	}
}