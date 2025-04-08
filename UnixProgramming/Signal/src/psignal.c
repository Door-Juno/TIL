#include <stdio.h>
#include <ctype.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <fcntl.h>

unsigned long cnt = 0; 
unsigned long max_prime = 2;
int signal_cnt = 0;

int is_prime(unsigned long);
void handle(int);

int main(){
    unsigned long n = 2;

    signal(SIGINT, handle);
    while (1){
        if(is_prime(n)){
            max_prime = n;
        }
        cnt ++;
        n ++ ;
    }
}

int is_prime(unsigned long n){
    if (n == 2 ){
        return 1;
    }
    for(unsigned long i = 2; i <= sqrt(n); i ++){
        if(n % i == 0 ){
            return 0;
        }
    }
    return 1;
}

void handle(int signum){
    signal_cnt ++;
    printf("현재 까지 확인한 정수 : %d\n",cnt);
    printf("가장 큰 소수: %d\n",max_prime);
    printf("Ctrl+C %d회 입력",signal_cnt);
    if(signal_cnt >= 3){
        printf("- 프로그램 종료\n");
        exit(1);
    }
}