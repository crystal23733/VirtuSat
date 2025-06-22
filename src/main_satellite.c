#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "sensor.h"

int main() {
    srand(time(NULL));

    printf("위성 작동 시작...\n");

    while(1) {
        // 센서 값 생성
        SensorData data = generate_sensor_data();

        // 데이터 출력
        printf("[센서] 온도: %.1f도 | 전압: %.2fV\n", data.temperature, data.voltage);

        sleep(1);
    }

    return 0;
}
