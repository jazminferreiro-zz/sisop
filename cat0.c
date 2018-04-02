#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define STDOUT 1

void cat0(const char *file);
ssize_t read_and_print(int file_descriptor);

ssize_t read_and_print(int file_descriptor){
	char buffer[BUF_SIZE];
	memset(buffer, 0, BUF_SIZE);

	ssize_t bytes_read = read(file_descriptor, &buffer, BUF_SIZE);
	ssize_t total_bytes_read =  bytes_read;
	while(bytes_read > 0 && total_bytes_read < BUF_SIZE){
		bytes_read = read(file_descriptor, &buffer[total_bytes_read], BUF_SIZE- total_bytes_read);
		total_bytes_read += bytes_read;
	}

	ssize_t bytes_written = write(STDOUT, &buffer, BUF_SIZE);
	
	while(bytes_written < total_bytes_read  && bytes_written < BUF_SIZE){
		bytes_written += write(1, &buffer[bytes_written], BUF_SIZE- bytes_written);
	}
	return bytes_read;
}


void cat0(const char *file) {
	int file_descriptor = open(file,O_RDONLY);
	if(file_descriptor < 0){
		printf("open() failed with error [%s]\n",strerror(errno)); 
	}
	ssize_t bytes_read = read_and_print(file_descriptor);
	while(bytes_read > 0){
		bytes_read = read_and_print(file_descriptor);
	}
	close(file_descriptor); 
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("Missing operand\n");
	}
    cat0(argv[1]);
}