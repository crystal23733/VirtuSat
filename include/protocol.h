#ifndef PROTOCOL_H
#define PROTOCOL_H

#define MAX_MESSAGE_LEN 128

typedef enum {
    CMD_TEMP,
    CMD_VOLT,
    CMD_STAT,
    CMD_PING,
    CMD_RESET,
    CMD_UNKNOWN,
    CMD_EXIT
} CommandType;

typedef  struct {
    float temperature;
    float voltage;
} SensorData;

// 명령 파싱 함수
CommandType parse_command(const char* message);

#endif
