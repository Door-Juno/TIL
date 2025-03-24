// cp1.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFERSIZE  4096
#define COPYMODE    0644

void oops(char *, char *);

int main(int ac, char *av[]) {
    int in_fd, out_fd, n_chars;
    char buf[BUFFERSIZE];

    // Check args 
    if( ac != 3 ) {
        fprintf(stderr,"usage: %s source destination\n", *av);
        exit(1);
    }

    //Open Files
    if((in_fd = open(av[1],O_RDONLY)) == -1 ){
        oops("Cannot Open", av[1]);
    }
    if((out_fd = creat( av[2], COPYMODE)) == -1 ){
        oops("Cannot Creat", av[2]);
    }

    //Copy Files
    while( (n_chars = read(in_fd,buf,BUFFERSIZE)) > 0){
        if (write (out_fd, buf, n_chars) != n_chars){
            oops("Write error to", av[2]);
        }
    }
    if( n_chars == -1) {
        oops("Read error from ", av[1]);
    }
    
    //Close File
    if( close(in_fd) == -1 || close(out_fd) == -1 ){
        oops("Error closing files", "");
    }
}

void oops(char *s1, char *s2){
    fprintf(stderr, "ERROR : %s",s1);
    perror(s2);
    exit(1);
}