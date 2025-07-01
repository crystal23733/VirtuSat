#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "sensor.h"
#include "network.h"
#include "protocol.h"

int main() {
    srand(time(NULL));

    printf("위성 작동 시작...\n");

    // 서버 시작
    int server_fd = start_server();

    // 지상국 연결 기다리기
    int client_fd = accept_connection(server_fd);

    char buffer[BUFFER_SIZE];

    while(1) {
        int received = receive_message(client_fd, buffer, BUFFER_SIZE);
        if (received <= 0) {
            printf("[위성] 수신 실패 또는 연결 종료\n");
            break;
        }

        CommandType cmd = parse_command(buffer);

        // 센서 값 생성
        SensorData data = generate_sensor_data();

        char response[BUFFER_SIZE];
        if (cmd == CMD_TEMP) {
            sprintf(response, "TEMP:%.1f", data.temperature);
        } else if (cmd == CMD_VOLT) {
            sprintf(response, "VOLT:%.2f", data.voltage);
        } else if (cmd == CMD_STAT) {
            sprintf(response, "STAT:TEMP=%.1f;VOLT=%.2f", data.temperature, data.voltage);
        } else if (cmd == CMD_PING) {
            strcpy(response, "ACK:PING_OK");
        } else {
            strcpy(response, "ERR:UNKNOWN_CMD");
        }

        send_message(client_fd, response);
        printf("[위성] -> 응답 전송: %s\n", response);
    }

    return 0;
}
