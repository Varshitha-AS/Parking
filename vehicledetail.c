#include "program.h"

void saveVehicleDetails(int slot_number, bool isTwoWheeler, const char* reg, time_t entry_time) {
    FILE *file = fopen(VEHICLE_DETAILS_FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file for writing vehicle details.\n");
        return;
    }

char entry_time_str[26];
    formatTime(entry_time_str, sizeof(entry_time_str), entry_time);

    fprintf(file, "Slot Number: %d\n", slot_number);
    fprintf(file, "Vehicle Type: %s\n", isTwoWheeler ? "Two-Wheeler" : "Four-Wheeler");
    fprintf(file, "Vehicle Registration: %s\n", reg);
    fprintf(file, "Entry Time: %s\n", entry_time_str);
    fprintf(file, "--------------------\n");

    fclose(file);
}
