#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

void show_stat_info( char * , struct stat * ) ;

int main( int ac, char *av[] ) {
    struct stat info;

    if (ac > 1){
        if( stat(av[1],&info) != -1) {
            show_stat_info (av[1],&info);
            return 0;
        }
    }
    else {
        perror(av[1]);
    }

    return 1;
}

void show_stat_info(char *fname, struct stat *buf) {
    printf("   mode: %o\n", buf->st_mode);	/* type + mode */
    printf("  links: %d\n",(int)buf->st_nlink);	/* # links     */
    printf("   user: %d\n", buf->st_uid);	/* user id     */
    printf("  group: %d\n", buf->st_gid);	/* group id    */
    printf("   size: %d\n",(int)buf->st_size); 	/* file size   */
    printf("modtime: %d\n",(int)buf->st_mtime);	/* modified    */
    printf("   name: %s\n", fname );		/* filename    */
}