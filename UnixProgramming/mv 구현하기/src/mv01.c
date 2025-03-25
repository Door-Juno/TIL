/*
mv01.c
1. 명령어를 인자로 받음... ac = 3 , av = ["./mv01", "from" , "to"]
2. av[2] is file ? 
2-1. true -> rename()
2-2. flase .. 디렉토리로 이동.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


int is_dir(const char *path);
void addstring(char *real_path, size_t size, const char *dir,const char *filename);

int main(int ac, char* av[]) {
    char path[PATH_MAX];

    if( ac != 3 ) {
        fprintf(stderr,"명령어 똑바로 치세여 ~\n");
        exit(1);
    }

    char *src = av[1];
    char *dst = av[2];

    // dst가 dir이라면 !
    // rename 쓸때.. 뒷쪽인자에 "dst/src" 로 하면 파일 이동 가능
    // 그럼 .... 문자열 합성을 해야함
    if(is_dir(dst)){
        // 문자열 합성
        addstring(path, sizeof(path),dst,src);
        if(rename(src,path) == -1 ){
            fprintf(stderr,"파일 이동 실패\n");
            exit(1);
        }
    }

    // dst가 file이라면 !
    else {
        if(rename(src,dst) == -1 ){
            fprintf(stderr,"파일 리네임 실패..\n");
            exit(1);
        }
    }
    


}

int is_dir(const char *path){
    struct stat info;
    if(stat(path, &info) == -1 ) return 0;
    return S_ISDIR(info.st_mode);
}

void addstring(char *real_path, size_t size, const char *dir,const char *filename){
    snprintf(real_path, size, "%s/%s",dir,filename);
}