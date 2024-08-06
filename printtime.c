#include "program.h"

void printTime(const char* label, time_t time_value) {
    char buffer[26];
    formatTime(buffer, sizeof(buffer), time_value);
    printf("%s: %s\n", label, buffer);
}