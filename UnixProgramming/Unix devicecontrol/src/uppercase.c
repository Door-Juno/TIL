#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define OLCUC 0x0002

int main() {
    struct termios info;

    // 현재 터미널 속성 가져오기
    tcgetattr(STDOUT_FILENO, &info);

    // OLCUC 비트 토글 ON
    info.c_oflag ^= OLCUC;

    // 적용
    tcsetattr(STDOUT_FILENO, TCSANOW, &info);

    // 현재 상태 출력
    if (info.c_oflag & OLCUC) {
        printf("OLCUC bit is on\n");
    } else {
        printf("OLCUC bit is off\n");
    }

    return 0;
}
