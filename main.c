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
