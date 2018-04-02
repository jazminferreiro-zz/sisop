#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define COUNTS 1

void cp(char * origin_file, char * new_file){
	int origin_file_fd = open(origin_file,O_RDONLY |O_CLOEXEC);
	int new_file_fd = open(new_file,O_CREAT | O_WRONLY, 0664);

	char buffer[COUNTS];
	size_t bytes_read;

	while(bytes_read > 0){
		memset(buffer, 0,COUNTS);
		bytes_read = read(origin_file_fd, buffer, COUNTS);
		write(new_file_fd, buffer, bytes_read);
	} 
	close(origin_file_fd);
	close(new_file_fd);

}

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("cp0: operand missing\nTry ln --help\n");
	}else{
		cp(argv[1], argv[2]);
	}
}