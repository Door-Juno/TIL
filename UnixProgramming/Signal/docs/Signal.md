# Signal
* 리눅스 체제에서 `Ctrl-C`를 누르면 프로그램이 종료된다. 바로 이것이 Signal이다.

### 1. Signal이란?
* Signal은 커널이 프로세스에게 보내는 일종의 비동기 메세지이다.
* 예를 들어 사용자가 `Ctrl-C`를 누르면 커널은 현재 프로세스에 `SIGINT(Interrupt Signal)`을 보내게 된다.

### 2. Signal의 종류
* Signal의 분류

| 유형      | 예시 시그널   | 설명                                     |
|-----------|---------------|------------------------------------------|
| 동기적    | SIGFPE, SIGSEGV | 프로그램 내부에서 발생 (예: 0으로 나누기, 잘못된 포인터 접근) |
| 비동기적  | SIGINT, SIGTERM, SIGKILL | 외부 이벤트로 발생 (예: Ctrl-C, `kill` 명령)      |

* Signal의 종류

| 시그널 이름 | 번호 | 기본 동작       | 설명                        |
|-------------|------|----------------|-----------------------------|
| SIGINT      | 2    | 종료           | 인터럽트 시그널 (Ctrl-C)    |
| SIGTERM     | 15   | 종료           | 종료 요청 (`kill` 명령 기본) |
| SIGKILL     | 9    | 즉시 종료 (무시 불가) | 강제 종료 (`kill -9`)     |
| SIGQUIT     | 3    | 코어 덤프 후 종료 | Ctrl-\ 입력 시 발생         |

* 전체 시그널 목록은 `man 7 signal`에서 확인 가능하다.

### 3. Signal 처리 방법
``` c
#include <signal.h>

signal(SIGINT,SIG_DFL); //기본 동작
signal(SIGINT,SIG_IGN); //무시
signal(SIGINT,my_handler); // 사용자의 handler함수 실행

```
* `SIG_DF:` : 기본 동작 수행
* `SIG_IGN` : 무시
* `my_handler` : `my_handler`함수 실행

### 4. Signal Handler 예제 코드
``` c
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
```
* 다음 코드를 살펴보자. 대충 보니, 현재까지 확인한 정수와 그 사이에서의 가장 큰 소수를 `Ctrl+C`입력이 들어올때마다 출력하는 것을 볼 수 있다.
* `signal_cnt`를 통해 3회 출력후 종료하는것을 볼 수 있다.
``` c
ignal(SIGINT, handle); 
.
.
.
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
```
* `Ctrl+C`입력이 들어올때마다 `handle` 실행.
``` bash
$ ./psignal
^C
현재 까지 확인한 정수 : 4450149
가장 큰 소수 : 4450139
Ctrl+C 1회 입력
^C
현재 까지 확인한 정수 : 6642849
가장 큰 소수 : 6642847
Ctrl+C 2회 입력
^C
현재 까지 확인한 정수 : 10202609
가장 큰 소수 : 10202603
Ctrl+C 3회 입력
-프로그램 종료
$ >> 
```

### 5. 마무리하며
* Signal은 프로그램 외부에서 발생하는 비동기 이벤트입니다.

* 기본 동작은 종료지만, signal() 함수를 사용하여 커스터마이징이 가능합니다.
