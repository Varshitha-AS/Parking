#include "program.h"

void formatTime(char *buffer, size_t size, time_t time_value) {
    struct tm *tm_info = localtime(&time_value);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}
