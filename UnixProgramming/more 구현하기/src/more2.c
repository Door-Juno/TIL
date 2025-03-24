#include <stdio.h>
#include <stdlib.h>

#define PAGELEN 24 // 한번에 출력되는 단위
#define LINELEN 512 // 한줄 읽는 단위

void do_more(FILE * );
int see_more(FILE * ); // changed

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
    FILE *fp_tty ; //new

    //new
    fp_tty = fopen("/dev/tty", "r");
    if (fp_tty == NULL) 
        exit(1);

    while (fgets(line, LINELEN, fp)) { //파일 한줄씩 읽기
        if(num_of_lines == PAGELEN) {
            reply = see_more(fp_tty); //changed
            if( reply == 0 ) 
                break;
            num_of_lines -= reply;
        }
        if ( fputs(line,stdout) == EOF ) // 파일 출력
            exit(1);
        num_of_lines ++ ; //Count lines
    }
}

int see_more(FILE *cmd) {
    int c; 
    printf("\033 more? \033[m");
    while ( (c = getc(cmd)) != EOF ){ // changed
        if ( c == 'q')
            return 0;
        if ( c == ' ') //공백 입력시 24줄 출력
            return PAGELEN ;
        if ( c == '\n') //엔터 입력시 한줄
            return 1;
    }
    return 0;
}