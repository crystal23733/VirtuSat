#include <stdio.h>
#include <string.h>
#include "network.h"
#include "protocol.h"

int main() {
    char input[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    printf("VirtuSat 지상국 작동 시작...\n");

    // 위성과 연결 시도
    int sock = connect_to_server();

    while(1) {
        // 명령어 입력
        printf(">> 명령 입력 (TEMP. VOLT, STAT, PING): ");
        fgets(input, sizeof(input), stdin);

        // 문자열 끝 줄바꿈 제거
        input[strcspn(input, "\n")] = '\0';

        // 명령어 유효성 검사
        CommandType cmd = parse_command(input);
        if (cmd == CMD_UNKNOWN) {
            printf("[지상국] 잘못된 명령어입니다.\n");
            continue;
        }

        // 위성에 명령 전송
        if (send_message(sock, input) < 0) {
            printf("[지상국] 명령 전송 실패\n");
            break;
        }

        // 위성 응답 수신
        if (receive_message(sock, response, BUFFER_SIZE) < 0) {
            printf("[지상국] 응답 수신 실패!\n");
            break;
        }

        // 응답 출력
        printf("[응답] %s\n", response);

    }

    return 0;
}
