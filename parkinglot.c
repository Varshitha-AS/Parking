#include "program.h"
void initializeParkingLot() {
    memset(two_wheeler_slots_occupied, 0, sizeof(two_wheeler_slots_occupied));
    memset(four_wheeler_slots_occupied, 0, sizeof(four_wheeler_slots_occupied));
}