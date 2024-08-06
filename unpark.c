#include "program.h"
void unparkVehicle(bool isTwoWheeler) {
    int slot_number;
    printf("Enter slot number to unpark: ");
    while (scanf("%d", &slot_number) != 1 || slot_number < 1 || (isTwoWheeler && slot_number > MAX_TWO_WHEELER_SLOTS) || (!isTwoWheeler && slot_number > MAX_FOUR_WHEELER_SLOTS)) {
        printf("Invalid slot number. Enter again: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    while (getchar() != '\n'); // Clear input buffer

    if ((isTwoWheeler && !two_wheeler_slots_occupied[slot_number - 1]) || (!isTwoWheeler && !four_wheeler_slots_occupied[slot_number - 1])) {
        printf("Slot is not occupied.\n");
        return;
    }

    time_t exit_time = getCurrentTime();
    int fee;
    if (isTwoWheeler) {
        fee = TWO_WHEELER_DAILY_FEE;
        two_wheeler_slots_occupied[slot_number - 1] = false;
        total_amount_collected_two_wheelers += fee;
        total_amount_collected += fee;
        generateSlip(slot_number, true, two_wheeler_entry_time[slot_number - 1], exit_time, fee);
    } else {
        fee = FOUR_WHEELER_DAILY_FEE;
        four_wheeler_slots_occupied[slot_number - 1] = false;
        total_amount_collected_four_wheelers += fee;
        total_amount_collected += fee;
        generateSlip(slot_number, false, four_wheeler_entry_time[slot_number - 1], exit_time, fee);
    }

    printf("Vehicle unparked from slot %d.\n", slot_number);
    printTime("Exit Time", exit_time);
    printf("Fee collected: ₹%d\n", fee); // Debug print
}