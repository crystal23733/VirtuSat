#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include "network.h"
#include "protocol.h"

FILE *log_file = NULL;

// 종료 시 안전하게 파일을 닫는 함수
void cleanup(int sig) {
    if (log_file) {
        fclose(log_file);
    }
    printf("\n[지상국] 안전 종료 완료.\n");
    exit(0);
}

int main() {
    char input[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    signal(SIGINT, cleanup);

    printf("VirtuSat 지상국 작동 시작...\n");

    // 위성과 연결 시도
    int sock = connect_to_server();

    // 로그 파일 열기
    log_file = fopen("data/ground_log.csv", "w");
    if (!log_file) {
        printf("[지상국] 로그 파일 열기 실패\n");
        return 1;
    }
    fprintf(log_file, "type,value\n");

    while(1) {
        // 명령어 입력
        printf(">> 명령 입력 (TEMP. VOLT, STAT, PING): ");
        fgets(input, sizeof(input), stdin);

        // 문자열 끝 줄바꿈 제거
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "EXIT") == 0) {
            printf("[지상국] EXIT 명령으로 종료합니다.\n");
            break;
        }

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

        float temp = 0, volt = 0;

        if (strstr(response, "VOLT")) {
            sscanf(response, "TEMP:%f", &temp);
            fprintf(log_file, "TEMP, %.2f\n", temp);
        } else if (strstr(response, "VOLT:")) {
            sscanf(response, "VOLT:%f", &volt);
            fprintf(log_file, "VOLT, %.2f\n", volt);
        } else if (strstr(response, "STAT:")) {
            sscanf(response, "STAT:TEMP=%f;VOLT%f", &temp, &volt);
            fprintf(log_file, "TEMP,%.2f\n", temp);
            fprintf(log_file, "VOLT,%.2f\n", volt);
        }

        if (temp >= 70.0) {
            printf("[경고] 온도가 70도를 초과했습니다! 현재: %.2f\n", temp);
        }

        fflush(log_file); // 즉시 파일에 기록
    }

    cleanup(0);
    return 0;
}
