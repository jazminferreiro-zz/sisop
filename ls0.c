#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

	

# define PATHNAME 1
# define STDOUT 1
# define NAME_LEGTH 256

void initialize_array(char array[], int length);
void ls0(const char * pathname);

void initialize_array(char array[], int length){
	for(int i = 0; i< length; i++){
    	array[i] = 0;
    }
}

void ls0(const char * pathname) {
    printf("%s\n",pathname );
    DIR * dir = opendir(pathname);
    if(dir == NULL){
    	char error_description[256];
		snprintf(error_description, 256, "Error at opening directory %s", pathname );
    	perror(error_description); 
    }

    struct dirent * dir_entry = readdir(dir);
    while(dir_entry != NULL){
    	char name[NAME_LEGTH];
    	initialize_array(name, NAME_LEGTH);
		snprintf(name, NAME_LEGTH, "%s\n", dir_entry->d_name );
    	write(STDOUT,&name, NAME_LEGTH );
    	dir_entry = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
	if(argc > 1){
		ls0(argv[PATHNAME]);
	}else{
		char * pathname = get_current_dir_name();
		ls0(pathname);
	}
    
}