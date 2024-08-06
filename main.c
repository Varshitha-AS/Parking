#include "program.h"
#include "availableslot.c"
#include "formatetime.c"
#include "grnarateslip.c"
#include "parkinglot.c"
#include "parkinslot.c"
#include "printtime.c"
#include "summaryrepoart.c"
#include "time.c"
#include "unpark.c"
#include "vehicledetail.c"
#include "viewvehicle.c"


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
