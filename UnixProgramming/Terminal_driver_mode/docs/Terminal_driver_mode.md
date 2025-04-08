# 터미널 드라이버의 모드
### 1. Terminal driver 
* 리눅스에서 터미널은 단순한 입력 장치가 아니다.
  커널의 터미널 드라이버(tty)가 입력을 받아서 처리해주는 중간 매개체 역할을 한다.
* 기본적으로 터미널은 사용자의 키보드 입력을 버퍼에 저장하고, Enter키가 눌릴때 까지 프로그램에 전달하지 않는다.

### 2. Terminal driver의 3가지 모드
* `Canonical` : 기본 입력 방식 - 줄 단위 입력, 편집 가능, 백스페이스와 Ctrl 등을 처리한다.
* `Noncanonical` : 즉시 입력 전달 - 실시간 반응, 편집 불가, 일부 제어 문자 처리 유지 .
* `Raw` : 가장 낮은 수준의 제어 - 모든 입력을 가공 없이 바로 전달한다.

* 다음으로 보여질 `rotate.c`는 입력받은 문자를 다음 문자로 출력하는 코드이다.
``` c
// rotate.c
#include <stdio.h>
#include <ctype.h>

int main(){
    int c ;
    while ( (c = getchar()) != EOF ){
        if( c== 'z' ){
            c = 'a';
        }
        else if (islower(c)){
            c ++;
        }
        puchar(c)
    }
}
```
``` bash
$ ./rotate
abx(백스페이스!)cd (엔터!)
bcde
^C
$
```
* 이 코드의 출력결과와 같이 터미널을 통한 입력은 엔터를 통해 구분되며 도중에 수정이 가능하다.(백스페이스를 통해 x를 지움)

### 3. Using icanon
* 우리는 stty 명령어를 통해 터미널의 설정을 직접 바꿀수있다.
* `stty -icanon;` 을 사용해 `Noncanonical`상태로 바꾸어준 후 다시 함수를 실행해보자.
``` bash 
$ stty -icanon
$ ./rotate
abbcxy^?cdde
effggh^C
$ stty icanon 
```
* 출력을 보자. 입력은 위와 동일하게 abx(백스페이스)cd(엔터)efg(Ctrl + C)를 했는데, 실시간으로 입력을 처리하는 모습이다.
* 우리는 터미널에는 `stty` 명령어로, 혹은 C에서는 `tcsetattr`을 통해 코드로 터미널 설정을 조절할 수 있다는 것을 이미 알고있다.

### 4. `termios.h`를 통해 터미널 직접 제어하기
* EX : play_again1.c
``` c
/* play_again1.c
 *	purpose: ask if user wants another transaction
 *	 method: set tty into char-by-char mode, read char, return result
 *	returns: 0 => yes, 1 => no
 *	 better: do no echo inappropriate input
 */
#include	<stdio.h>
#include	<termio.h>

#define QUESTION	"Do you want another transaction"
int get_response( char * );
void set_crmode(void);
void tty_mode(int);

int main()
{
	int response;
	tty_mode(0);				
	set_crmode();				
	response = get_response(QUESTION);
	tty_mode(1);				
	return response;
}

int get_response(char *question)
{
	int input;
	printf("%s (y/n)?", question);
	while(1){
		switch( input = getchar() ) {
			case 'y':
			case 'Y': return 0;
			case 'n':
			case 'N':
			case EOF: return 1;
			default:
				printf("\ncannot understand %c, ", input);
				printf("Please type y or no\n");
		}
	}
}

void set_crmode(void)
{
	struct termios ttystate;
	
	tcgetattr( 0, &ttystate);		
	ttystate.c_lflag	&= ~ICANON;
	ttystate.c_cc[VMIN]	= 1;
	tcsetattr( 0, TCSANOW, &ttystate);
}
void tty_mode(int how)
{
	static struct termios original_mode;
	if( how == 0 )
		tcgetattr(0, &original_mode);
	else
		tcsetattr(0, TCSANOW, &original_mode);

}
```
* 출력 결과
``` bash
$ ./play_again1
Do you want another transaction (y/n)? s
cannot understand s, Please type y or no
u
cannot understand u, Please type y or no
r
cannot understand r, Please type y or no
e
cannot understand s, Please type y or no
y $
```
* 코드를 살펴보도록 하자.
``` c
int main()
{
	int response;
	tty_mode(0);				
	set_crmode();				
	response = get_response(QUESTION);
	tty_mode(1);				
	return response;
}
```
* `main`함수는 `tty_mode(0)`을 통해 현재의 tty mode를 저장하고, `set_crmode()`를 통해 tty mode를 수정을 한다.
* `get_response`를 통해 사용자의 입력을 받고 종료되면 `tty_mode(1)`을 통해 원래의 tty mode로 돌아가는 구조이다.
``` c
void set_crmode(void){
    struct termios ttystate;
    tcgetattr(0,&ttystate);
    ttystate.c_lflag &= ~ICANNON;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr(0,TCSANOW,&ttystate);
}
```
* `set_crmode`는 `ICANNON` 모드를 비활성화 시키고, 수정된 설정을 적용한다.
* `ttystate.c_cc[VMIN]`은 제어 문자를 설정하는데 사용되는데, 
`VMIN`은 입력을 기다릴때 필요한 최소 문자 수를 의미한다.
    * `VMIN = 1` -> 한 글자 들어오면 즉시 반환
    * `VMIN = 0` -> 입력이 없어도 즉시 반환

* EX: timeout 적용하기 (특정 시간이 지나면 강제종료)
``` c
/* play_again3.c
 *	purpose: ask if user wants another transaction
 *	 method: set tty into char-by-char mode, no echo mode
 *		 set tty into no-delay mode
 *		 read char, return result
 *	returns: 0 => yes, 1 => no, 2 => timeout
 *	 better: reset terminal mode on Interrupt
 */
#include	<stdio.h>
#include	<termio.h>
#include	<fcntl.h>
#include	<string.h>

#define ASK		"Do you want another transaction"
#define TRIES		3		/* max tries */
#define SLEEPTIME 	2		/* time per try */
#define BEEP		putchar('\a')	/* alert user */

int get_response( char *, int );
void set_cr_noecho_mode(void);
void set_nodelay_mode(void);
void tty_mode(int);

int main()
{
	int response;

	tty_mode(0);			
	set_cr_noecho_mode();		
	set_nodelay_mode();			
	response = get_response(ASK, TRIES);	
	tty_mode(1);				
	return response;
}

int get_response(char *question, int maxtries)
{
	int 	input;
	printf("%s (y/n)?", question);	
	fflush(stdout);				
	while(1){
		sleep(SLEEPTIME);		
		input = tolower( get_ok_char());
		if( input == 'y')
			return 0;
		if( input == 'n')
			return 1;
		if( maxtries-- == 0 )	
			return 2;		
		BEEP;
	}
}
int get_ok_char(void)
{
	int c;
	while( ( c = getchar() != EOF && strchr("yYnN", c) == NULL))
		;

	return c;
}

void set_cr_noecho_mode(void)
{
	struct termios ttystate;
	
	tcgetattr( 0, &ttystate);		
	ttystate.c_lflag	&= ~ICANON;	
	ttystate.c_lflag	&= ~ECHO;	
	ttystate.c_cc[VMIN]	= 1;		
	tcsetattr( 0, TCSANOW, &ttystate);	
}

void set_nodelay_mode(void)
{
	int termflags;
	termflags = fcntl(0, F_GETFL);	
	termflags |= O_NDELAY;			
	fcntl(0, F_SETFL, termflags);		
}
void tty_mode(int how)
{
	static struct termios original_mode;
	static int	      original_flags;

	if( how == 0 ){
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
	}
	else{
		tcsetattr(0, TCSANOW, &original_mode);
		original_flags = fcntl(0, F_SETFL, original_flags);
	}

}
```
* `get_response`를 살펴보자.
``` c
int get_response(char *question, int maxtries)
{
	int 	input;
	printf("%s (y/n)?", question);	
	fflush(stdout);				
	while(1){
		sleep(SLEEPTIME);		
		input = tolower( get_ok_char());
		if( input == 'y')
			return 0;
		if( input == 'n')
			return 1;
		if( maxtries-- == 0 )	
			return 2;		
		BEEP;
	}
}
```
* `sleep(SLEEPTIME)`을 사용해 실행에 지연을 일으킨다.
* `SLEEPTIME = 2`이므로 while문은 대략 2초에 한번 순회되고, `maxtries = 0`이 될때 `return 2`를 한다. 즉, `maxtries = 3` 이므로, 총 6초 후에 입력이 없다면 종료하게 된다.

### 5. 마무리
- 터미널 입력 방식은 Canonical, Noncanonical, Raw 모드로 나뉜다.
- `termios.h`를 이용하면 코드 상에서 직접 입력 처리 방식 제어 가능.
- `VMIN`을 통해 입력을 기다리는 최소 문자를 지정할 수 있다.
- `play_again1.c`, `play_again3.c`는 실시간 입력 및 타임아웃 구현의 좋은 예시이다.
- 다음은 `Ctrl-C`와 같은 인터럽트를 다르는 Signal처리에 대해 공부할 것이다.