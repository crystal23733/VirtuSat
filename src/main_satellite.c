#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sensor.h"
#include "network.h"
#include "protocol.h"

int main() {
    srand(time(NULL));

    printf("위성 작동 시작...\n");

    // [1] 서버 시작
    int server_fd = start_server();

    // [2] 지상국 연결 기다리기
    int client_fd = accept_connection(server_fd);

    // [3] 1회용 수신 테스트
    char buffer[BUFFER_SIZE];
    int received = receive_message(client_fd, buffer, BUFFER_SIZE);

    if (received > 0) {
        printf("[위성] 받은 명령: %s\n", buffer);
    } else {
        printf("[위성] 수신 실패\n");
    }

    while(1) {
        // 센서 값 생성
        SensorData data = generate_sensor_data();

        // 데이터 출력
        printf("[센서] 온도: %.1f도 | 전압: %.2fV\n", data.temperature, data.voltage);

        sleep(1);
    }

    return 0;
}
