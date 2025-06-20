#include <stdlib.h>
#include <time.h>
#include "sensor.h"

// 센서값 생성 함수
SensorData generate_sensor_data() {
    SensorData data;

    srand(time(NULL));

    // 20도 ~ 35도 사이 온도 (소수점 포함)
    data.temperature = 20.0f + (rand() % 150) / 10.0f;

    // 3.0V ~ 4.2V 사이 전압
    data.voltage = 3.0f + (rand() % 120) / 100.0f;

    return data;
}