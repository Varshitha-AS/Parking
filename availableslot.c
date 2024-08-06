#include "program.h"

void displayAvailableSlots(bool isTwoWheeler) {
    printf("\nAvailable Parking Slots for %s:\n", isTwoWheeler ? "Two-Wheelers" : "Four-Wheelers");

    if (isTwoWheeler) {
        printf("Two-Wheeler Slots:\n");
        for (int i = 0; i < MAX_TWO_WHEELER_SLOTS; i++) {
            if (!two_wheeler_slots_occupied[i]) {
                printf("Slot %d is available.\n", i + 1);
            }
        }
    } else {
        printf("Four-Wheeler Slots:\n");
        for (int i = 0; i < MAX_FOUR_WHEELER_SLOTS; i++) {
            if (!four_wheeler_slots_occupied[i]) {
                printf("Slot %d is available.\n", i + 1);
            }
        }
    }
}
