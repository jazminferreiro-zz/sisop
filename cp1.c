#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>



#define ORIGIN_FILE 1
#define DESTINATION_FILE 2

void cp(char * origin_file, char * new_file){
	int origin_file_fd = open(origin_file,O_RDONLY |O_CLOEXEC);
	 if(origin_file_fd < 0){
    	perror("open origin file failed with error"); 
    	return;
	}
	int new_file_fd = open(new_file,O_CREAT | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
	 if(new_file_fd < 0){
    	perror("open destination file failed with error"); 
    	close(origin_file_fd);
    	return;
	}

	ssize_t origin_file_size = lseek(origin_file_fd, 0, SEEK_END);
	ftruncate(new_file_fd , origin_file_size);

	printf("origin file size: %li\n",origin_file_size );

	int page_size = sysconf(_SC_PAGE_SIZE) - 1;
	int buffer_size = page_size;

	char *p_origin_file;
	char *p_new_file;
	off_t offset = 0;
	 

	while(offset < origin_file_size){

		if(offset + buffer_size > origin_file_size){
			buffer_size = origin_file_size -offset;
		}

		p_origin_file = mmap (NULL, buffer_size, PROT_READ, MAP_SHARED, origin_file_fd, offset);
		if (p_origin_file == MAP_FAILED){
        	perror("mmap origin file ");
        	close(origin_file_fd);
			close(new_file_fd);
			return;
		}
		printf("%s\n",p_origin_file );


		p_new_file = mmap (NULL, buffer_size, PROT_WRITE, MAP_SHARED, new_file_fd, offset);
		if (p_new_file == MAP_FAILED){
        	perror("mmap new file ");
        	close(origin_file_fd);
			close(new_file_fd);
			return;
		}

		memcpy(p_new_file,p_origin_file, buffer_size -1);
		
		offset = offset + page_size;

      
	}

	


	close(origin_file_fd);
	close(new_file_fd);

}

int main(int argc, char *argv[]) {
	if(argc < 3){
		printf("cp0: operand missing\nTry ln --help\n");
	}else{
		cp(argv[ORIGIN_FILE], argv[DESTINATION_FILE]);
	}
}