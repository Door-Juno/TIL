#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// #include <linux/limits.h>

void do_ls(char[]);

struct stat info;

int main (int ac, char *av[])
{
    if( ac == 1){
		do_ls(".");
    }
    else
		while( --ac ){
			do_ls( *++av );
		}
}

void do_ls(char dirname[]) {
    char path[PATH_MAX];
    DIR *dir_ptr;
    struct dirent *direntp;
    struct stat info;

    // 디렉토리 경로 출력
    printf("\n%s:\n", dirname);

    // 디렉토리 열고
    if ((dir_ptr = opendir(dirname)) == NULL) {
        fprintf(stderr, "cannot open %s\n", dirname);
        return;
    }

    // 파일 및 디렉토리 이름 출력
    while ((direntp = readdir(dir_ptr)) != NULL) {
        // 숨김 파일 무시
        if (direntp->d_name[0] == '.')
            continue;

        // 전체 경로 생성
        snprintf(path, sizeof(path), "%s/%s", dirname, direntp->d_name);

        // 정보 얻기
        if (stat(path, &info) == -1) {
            perror("stat error");
            continue;
        }

        // 그냥 이름만 출력
        printf("%s\n", direntp->d_name);
    }

    closedir(dir_ptr);

    // 디렉토리들만 재귀 탐색
    if ((dir_ptr = opendir(dirname)) == NULL)
        return;

    while ((direntp = readdir(dir_ptr)) != NULL) {
        if (direntp->d_name[0] == '.')
            continue;

        snprintf(path, sizeof(path), "%s/%s", dirname, direntp->d_name);
        if (stat(path, &info) == -1)
            continue;

        if (S_ISDIR(info.st_mode)) {
            do_ls(path);  // 재귀 호출
        }
    }

    closedir(dir_ptr);
}