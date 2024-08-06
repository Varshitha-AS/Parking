#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TWO_WHEELER_SLOTS 30
#define MAX_FOUR_WHEELER_SLOTS 20
#define TWO_WHEELER_DAILY_FEE 10
#define FOUR_WHEELER_DAILY_FEE 30
#define VEHICLE_DETAILS_FILENAME "vehicle_details.txt"
#define SLIP_FILENAME "parking_slip.txt"
#define SUMMARY_REPORT_FILENAME "summary_report.txt"

// Slot arrays and other variables
bool two_wheeler_slots_occupied[MAX_TWO_WHEELER_SLOTS];
bool four_wheeler_slots_occupied[MAX_FOUR_WHEELER_SLOTS];
time_t two_wheeler_entry_time[MAX_TWO_WHEELER_SLOTS];
time_t four_wheeler_entry_time[MAX_FOUR_WHEELER_SLOTS];
char two_wheeler_registration[MAX_TWO_WHEELER_SLOTS][20];
char four_wheeler_registration[MAX_FOUR_WHEELER_SLOTS][20];
int total_amount_collected_two_wheelers = 0;
int total_amount_collected_four_wheelers = 0;
int total_amount_collected = 0;

// Function prototypes
void initializeParkingLot();
void displayAvailableSlots(bool isTwoWheeler);
time_t getCurrentTime();
void formatTime(char *buffer, size_t size, time_t time_value);
void printTime(const char* label, time_t time_value);
void saveVehicleDetails(int slot_number, bool isTwoWheeler, const char* reg, time_t entry_time);
void generateSlip(int slot_number, bool isTwoWheeler, time_t entry_time, time_t exit_time, int fee);
void generateSummaryReport();
void parkVehicle(bool isTwoWheeler);
void unparkVehicle(bool isTwoWheeler);
void viewVehicleDetails();

// Initialize parking lot
void initializeParkingLot() {
    memset(two_wheeler_slots_occupied, 0, sizeof(two_wheeler_slots_occupied));
    memset(four_wheeler_slots_occupied, 0, sizeof(four_wheeler_slots_occupied));
}

// Display available parking slots
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

// Get current time
time_t getCurrentTime() {
    return time(NULL);
}

// Format and return time as string
void formatTime(char *buffer, size_t size, time_t time_value) {
    struct tm *tm_info = localtime(&time_value);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", tm_info);
}

// Print time
void printTime(const char* label, time_t time_value) {
    char buffer[26];
    formatTime(buffer, sizeof(buffer), time_value);
    printf("%s: %s\n", label, buffer);
}

// Save vehicle details to file
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

// Generate parking slip
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

// Generate summary report
void generateSummaryReport() {
    FILE *file = fopen(SUMMARY_REPORT_FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing summary report.\n");
        return;
    }

    fprintf(file, "--- Parking System Summary Report ---\n");
    fprintf(file, "Total Amount Collected from Two-Wheelers: ₹%d\n", total_amount_collected_two_wheelers);
    fprintf(file, "Total Amount Collected from Four-Wheelers: ₹%d\n", total_amount_collected_four_wheelers);
    fprintf(file, "Total Amount Collected: ₹%d\n", total_amount_collected);
    fprintf(file, "--------------------------------------\n");

    fclose(file);
}

// Park vehicle
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

// Unpark vehicle
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


// View vehicle details
void viewVehicleDetails() {
    FILE *file = fopen(VEHICLE_DETAILS_FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file for reading vehicle details.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

// Main menu
int main() {
    int option;
    initializeParkingLot();

    while (true) {
        printf("\nParking System Menu:\n");
        printf("1. Park Two-Wheeler\n");
        printf("2. Park Four-Wheeler\n");
        printf("3. Unpark Two-Wheeler\n");
        printf("4. Unpark Four-Wheeler\n");
        printf("5. View Vehicle Details\n");
        printf("6. Generate Summary Report\n");
        printf("7. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        switch (option) {
            case 1:
                parkVehicle(true);
                break;
            case 2:
                parkVehicle(false);
                break;
            case 3:
                unparkVehicle(true);
                break;
            case 4:
                unparkVehicle(false);
                break;
            case 5:
                viewVehicleDetails();
                break;
            case 6:
                generateSummaryReport();
                printf("Summary report generated. Please check the file: %s\n", SUMMARY_REPORT_FILENAME);
                break;
            case 7:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
