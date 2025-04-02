#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main() {
    struct termios on_echo_t, off_echo_t;
    char password[100];

    while (1) {
        printf("Enter password: ");
        fflush(stdout);

        tcgetattr(STDIN_FILENO, &on_echo_t);

        off_echo_t = on_echo_t;

        // ECHO 비트 끄기
        off_echo_t.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO, TCSANOW, &off_echo_t);

        // 패스워드 입력
        scanf("%s",password);
        getchar();
        printf("\n");

        // ECHO 복원
        tcsetattr(STDIN_FILENO, TCSANOW, &on_echo_t);

        if (strcmp(password, "quit") == 0)
            printf("quit!!!!!!");
            break;

        printf("Your password is: %s\n", password);
    }

    return 0;
}
