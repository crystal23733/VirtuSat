#include <string.h>
#include "protocol.h"

// 문자열 명령어를 enum으로 변환
CommandType parse_command(const char* message) {
    if (strncmp(message, "TEMP", 4) == 0) {
        return CMD_TEMP;
    } else if (strncmp(message, "VOLT", 4) == 0) {
        return CMD_VOLT;
    } else if (strncmp(message, "STAT", 4) == 0) {
        return CMD_STAT;
    } else if (strncmp(message, "PING", 4) == 0) {
        return CMD_PING;
    } else if (strncmp(message, "RESET", 6) == 0) {
        return CMD_RESET;
    } else if (strncmp(message, "EXIT", 4) == 0) {
        return CMD_EXIT;
    } else if (strncmp(message, "CALIBRATE", 10) == 0) {
        return CMD_CALIBRATE;
    } else {
        return CMD_UNKNOWN;
    }
}
