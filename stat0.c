#define _POSIX_C_SOURCE 200809L


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#define S_IFMT 01700000

enum{

    S_IFSOCK = 0140000,   //socket
    S_IFLNK  = 0120000,   //symbolic link
    S_IFREG = 0100000,   //regular file
    S_IFBLK = 0060000,   //block device
    S_IFDIR = 0040000,   //directory
    S_IFCHR = 0020000,   //character device
    S_IFIFO = 0010000   //FIFO
};

#define BUFFER_SIZE 50

char * get_type( unsigned int file_type){
 switch(file_type){
    case(S_IFSOCK):
            return "socket\n";
            break;
        case(S_IFLNK):
            return "symbolic link\n";
            break;
        case(S_IFREG):
            return "regular file\n";
            break;
        case(S_IFBLK):
            return "block device\n";
            break;
        case(S_IFDIR):
            return "directory\n";
            break;
        case(S_IFCHR):
            return "character device\n";
            break;
        case(S_IFIFO):
            return "FIFO\n";
    }
    return " type not found";
}

void stat0(const char *file) {
	struct stat stat_struct;
    stat(file, &stat_struct);
    printf("Size: %li\nFile: %s\nType: %s\n ",stat_struct.st_size, file, get_type(stat_struct.st_mode & S_IFMT));
    
}

int main(int argc, char *argv[]) {
	if(argc < 2){
		printf("stat0: operand missing\nTry rm --help\n");
	}
    stat0(argv[1]);
}