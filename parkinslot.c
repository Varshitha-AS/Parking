
#include "program.h"
void parkVehicle(bool isTwoWheeler) {
    int slot_number;
    char reg[20];
    displayAvailableSlots(isTwoWheeler);

    printf("Enter slot number to park: ");
    while (scanf("%d", &slot_number) != 1 || slot_number < 1 || (isTwoWheeler && slot_number > MAX_TWO_WHEELER_SLOTS) || (!isTwoWheeler && slot_number > MAX_FOUR_WHEELER_SLOTS)) {
        printf("Invalid slot number. Enter again: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    while (getchar() != '\n'); // Clear input buffer

    if (isTwoWheeler) {
        if (two_wheeler_slots_occupied[slot_number - 1]) {
            printf("Slot is already occupied.\n");
            return;
        }
        printf("Enter vehicle registration number: ");
        if (scanf("%19s", reg) != 1) {
            printf("Invalid registration input.\n");
            return;
        }
        while (getchar() != '\n'); // Clear input buffer

        two_wheeler_entry_time[slot_number - 1] = getCurrentTime(); // Set entry time to current time
        strcpy(two_wheeler_registration[slot_number - 1], reg);
        two_wheeler_slots_occupied[slot_number - 1] = true;

        saveVehicleDetails(slot_number, true, reg, two_wheeler_entry_time[slot_number - 1]);

        printf("Two-wheeler parked at slot %d.\n", slot_number);
        printTime("Entry Time", two_wheeler_entry_time[slot_number - 1]);
    } else {
        if (four_wheeler_slots_occupied[slot_number - 1]) {
            printf("Slot is already occupied.\n");
            return;
        }
        printf("Enter vehicle registration number: ");
        if (scanf("%19s", reg) != 1) {
            printf("Invalid registration input.\n");
            return;
        }
        while (getchar() != '\n'); // Clear input buffer

        four_wheeler_entry_time[slot_number - 1] = getCurrentTime(); // Set entry time to current time
        strcpy(four_wheeler_registration[slot_number - 1], reg);
        four_wheeler_slots_occupied[slot_number - 1] = true;

        saveVehicleDetails(slot_number, false, reg, four_wheeler_entry_time[slot_number - 1]);

        printf("Four-wheeler parked at slot %d.\n", slot_number);
        printTime("Entry Time", four_wheeler_entry_time[slot_number - 1]);
    }
}