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
void displaySpecialties(void);
void displayWards(void);
void displayBedOccupancy(void);

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

int patientId[MAX_PATIENTS];
char patientName[MAX_PATIENTS][100];
int patientAge[MAX_PATIENTS];
int emergencyLevel[MAX_PATIENTS];
int patientSpecialty[MAX_PATIENTS];

int wardAdmission[MAX_PATIENTS];
int patientWard[MAX_PATIENTS];
int daysAdmitted[MAX_PATIENTS];
int assignedBed[MAX_PATIENTS];

double baseFee[MAX_PATIENTS];
double emergencySurcharge[MAX_PATIENTS];
double wardCost[MAX_PATIENTS];
double grossTotal[MAX_PATIENTS];
double discount[MAX_PATIENTS];
double finalPayable[MAX_PATIENTS];
double waitingTime[MAX_PATIENTS];

int patientCount = 0;
int specialtyQueue[SPECIALTIES_NUM] = {0};

int main (void) {
    
    int choice;
    
    printf("Smart Hospital & Resource Allocation System\n");
    
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice)
        {
            case 1:
                displaySpecialties();
                break;
                
            case 2:
                displayWards();
                break;
                
            case 3:
                displayBedOccupancy();
                break;
                
            default:
                printf("\nInvalid choice. Please select correct choice from main menu.\n");
        }
    } while (choice != 8);
    return 0;
}

void displayMenu(void)
{
    printf("\n====================================================\n");
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

void displaySpecialties(void)
{
    int i;

    printf("\n----------------------------------------------------\n");
    printf("DOCTOR SPECIALTIES\n");
    printf("----------------------------------------------------\n");

    printf("%-5s %-25s %-15s %-15s %-10s\n",
           "ID", "Specialty", "Fee", "Time", "Daily Cap");

    for (i = 0; i < SPECIALTIES_NUM; i++)
    {
        printf("%-5d %-25s LKR %-10.2f %-10d mins %-10d\n",
               i + 1,
               specialtyName[i],
               consultationFee[i],
               consultationTime[i],
               dailyPatientCap[i]);
    }
}

void displayWards(void)
{
    int i;

    printf("\n----------------------------------------------------\n");
    printf("HOSPITAL WARDS\n");
    printf("----------------------------------------------------\n");

    printf("%-5s %-30s %-15s %-10s\n",
           "ID", "Ward", "Daily Rate", "Capacity");

    for (i = 0; i < WARDS_NUM; i++)
    {
        printf("%-5d %-30s LKR %-10.2f %-10d\n",
               i + 1,
               wardName[i],
               dailyBedRate[i],
               bedCapacity[i]);
    }
}

void displayBedOccupancy(void)
{
    int i;
    int j;

    printf("\n====================================================\n");
    printf("                BED OCCUPANCY\n");
    printf("====================================================\n");

    for (i = 0; i < WARDS_NUM; i++)
    {
        printf("\nWard %d: %s\n", i + 1, wardName[i]);

        for (j = 0; j < bedCapacity[i]; j++)
        {
            if (bedOccupancy[i][j] == 0)
            {
                printf("Bed %02d: Available   ", j + 1);
            }
            else
            {
                printf("Bed %02d: Occupied   ", j + 1);
            }

            if ((j + 1) % 2 == 0)
            {
                printf("\n");
            }
        }

        printf("\n");
    }
}
