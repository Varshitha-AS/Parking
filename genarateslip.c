#include "program.h"

void generateSlip(int slot_number, bool isTwoWheeler, time_t entry_time, time_t exit_time, int fee) {
    FILE *file = fopen(SLIP_FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file for writing parking slip.\n");
        return;
    }

    char entry_time_str[26], exit_time_str[26];
    formatTime(entry_time_str, sizeof(entry_time_str), entry_time);
    formatTime(exit_time_str, sizeof(exit_time_str), exit_time);

    fprintf(file, "\n--- Parking Slip ---\n");
    fprintf(file, "Slot Number: %d\n", slot_number);
    fprintf(file, "Vehicle Type: %s\n", isTwoWheeler ? "Two-Wheeler" : "Four-Wheeler");
    fprintf(file, "Entry Time: %s\n", entry_time_str);
    fprintf(file, "Exit Time: %s\n", exit_time_str);
    fprintf(file, "Total Parking Fee: ₹%d\n", fee);
    fprintf(file, "--------------------\n");

    fclose(file);
}
