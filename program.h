#ifndef PARKING_SLOT_H_INCLUDED
#define PARKING_SLOT_H_INCLUDED

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

bool two_wheeler_slots_occupied[MAX_TWO_WHEELER_SLOTS];
bool four_wheeler_slots_occupied[MAX_FOUR_WHEELER_SLOTS];
time_t two_wheeler_entry_time[MAX_TWO_WHEELER_SLOTS];
time_t four_wheeler_entry_time[MAX_FOUR_WHEELER_SLOTS];
char two_wheeler_registration[MAX_TWO_WHEELER_SLOTS][20];
char four_wheeler_registration[MAX_FOUR_WHEELER_SLOTS][20];
int total_amount_collected_two_wheelers = 0;
int total_amount_collected_four_wheelers = 0;
int total_amount_collected = 0;

#endif
