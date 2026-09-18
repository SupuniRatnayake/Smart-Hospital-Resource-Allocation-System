//
//  main.c
//  Smart-Hospital-Resource-Allocation-System
//
//  Created by Supuni Ratnayake on 2026-09-18.
//

#include <stdio.h>

#define SPECIALTIES_NUM 4
#define WARDS_NUM 4
#define MAX_BEDS 20
#define MAX_PATIENTS 100

void displayMenu(void);

const char specialtyName[SPECIALTIES_NUM][30] = {
    "General Practice (OPD)",
    "Paediatrics",
    "Cardiology",
    "Neurology"
};

const double consultationFee[SPECIALTIES_NUM] = {
    1500.00,
    2500.00,
    4500.00,
    5000.00
};

const int consultationTime[SPECIALTIES_NUM] = {
    15,
    20,
    30,
    30
};

const int dailyPatientCap[SPECIALTIES_NUM] = {
    30,
    20,
    12,
    10
};

const char wardName[WARDS_NUM][30] = {
    "General Ward",
    "Paediatric Ward",
    "Surgical Ward",
    "ICU (Intensive Care Unit)"
};

const double dailyBedRate[WARDS_NUM] = {
    3000.00,
    6000.00,
    12000.00,
    25000.00
};

const int bedCapacity[WARDS_NUM] = {
    20,
    10,
    10,
    5
};

int bedOccupancy[WARDS_NUM][MAX_BEDS] = {0};

int main (void) {
    
    printf("Smart Hospital & Resource Allocation System\n");
    displayMenu();
    
    return 0;
}

void displayMenu(void)
{
    printf("\n");
    printf("====================================================\n");
    printf("       SMART HOSPITAL RESOURCE SYSTEM\n");
    printf("====================================================\n");
    printf("1. Display Doctor Specialties\n");
    printf("2. Display Hospital Wards\n");
    printf("3. Display Bed Occupancy\n");
    printf("4. Register Patient\n");
    printf("5. Display Patients by Priority\n");
    printf("6. Generate Performance Report\n");
    printf("7. Save Bed Status\n");
    printf("8. Exit\n");
    printf("====================================================\n");
}
