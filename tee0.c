#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <stdio.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#define BUF_SIZE 64

#define STDIN 0
#define STDOUT 1




ssize_t read_and_write(int fd_to_read,int fd_to_write);
int write_in_file(int bytes_total_read, int file_descriptor, const void * buffer);
void tee0(const char *file);
void initialize_array(char array[], int length);

//esta funcion sirve para usar en lugar de memcpy
void initialize_array(char array[], int length){
	for(int i = 0; i< length; i++){
    	array[i] = 0;
    }
}

int  write_in_file(const int total_bytes_read, int file_descriptor, const void * buffer){

	ssize_t bytes_written = write(file_descriptor, buffer, BUF_SIZE);
	ssize_t total_bytes_written =  bytes_written;
	
	while( total_bytes_written < total_bytes_read  && total_bytes_written < BUF_SIZE){
		
		bytes_written += write(file_descriptor, buffer+bytes_written, BUF_SIZE - bytes_written);

		if(bytes_written < 0){
			return -1;
		}

		total_bytes_written += bytes_written;
	}
	return 0;
}

ssize_t read_and_write(int fd_to_read,int fd_to_write){
	char buffer[BUF_SIZE];
	initialize_array(buffer, BUF_SIZE);

	ssize_t bytes_read = read(fd_to_read, &buffer, BUF_SIZE);
	ssize_t total_bytes_read =  bytes_read;
	while(bytes_read > 0 && total_bytes_read < BUF_SIZE){
		bytes_read = read(fd_to_read, &buffer[total_bytes_read], BUF_SIZE- total_bytes_read);

		if(bytes_read < 0){
    		perror("Error while reading");  
			return 0;
		}
		total_bytes_read += bytes_read;
	}

	int write_stdout = write_in_file( total_bytes_read, STDOUT, &buffer);
	int write_file = write_in_file( total_bytes_read, fd_to_write, &buffer);
	 
	if(write_file < 0 || write_stdout < 0 ){
	 	return 0;
	}
	

	return total_bytes_read;
}


void tee0(const char *file) {

    int file_descriptor = open(file, O_CREAT|  O_WRONLY, S_IRWXU | S_IRWXG | S_IRWXO);
    if(file_descriptor < 0){
    	perror("open() failed with error"); 
	}

	ssize_t bytes_read = read_and_write(STDIN, file_descriptor);

	while(bytes_read > 0){
		bytes_read = read_and_write(STDIN, file_descriptor);
	}

	close(file_descriptor);
}

int main(int argc, char *argv[]) {
	
	if(argc > 1){
		tee0(argv[1]);
	}
    
}