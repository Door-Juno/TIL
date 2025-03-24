#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24 // 한번에 출력되는 단위
#define LINELEN 512 // 한줄 읽는 단위

void do_more(FILE * );
int see_more();

int main(int ac , char *av[]){
    FILE *fp ;
    if(ac == 1 ) // 인자가 하나일때 정상 실행
        do_more(stdin);
    else
        while(--ac)
            if( (fp = fopen(*++av, "r")) != NULL) {
                do_more(fp);
                fclose(fp);
            }
            else   
                exit(1);
    return 0;
}

void do_more(FILE *fp) {
    char line[LINELEN];
    int num_of_lines = 0 ;
    int see_more() , reply ;

    while (fgets(line, LINELEN, fp)) { //파일 한줄씩 읽기
        if(num_of_lines == PAGELEN) {
            reply = see_more();
            if( reply == 0 ) 
                break;
            num_of_lines -= reply;
        }
        if ( fputs(line,stdout) == EOF ) // 파일 출력
            exit(1);
        num_of_lines ++ ; //Count lines
    }
}

int see_more() {
    int c; 
    printf("\033 [more? \033[m");
    while ( (c = getchar()) != EOF ){ // 입력 받기
        if ( c == 'q')
            return 0;
        if ( c == ' ') //공백 입력시 24줄 출력
            return PAGELEN ;
        if ( c == '\n') //엔터 입력시 한줄
            return 1;
    }
    return 0;
}