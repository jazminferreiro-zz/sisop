#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>

void ln1(char * origin_file, char * new_link){
	int link(origin_file, new_link);
}

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("ln0: operand missing\nTry ln --help\n");
	}else{
		ln1(argv[1],argv[2]);
	}
}