#include "program.h"
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
