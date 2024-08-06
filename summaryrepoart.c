#include "program.h"

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