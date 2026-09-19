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
void registerPatient(void);
void assignBed(int patientIndex);
double calculateWaitingTime(int specialtyIndex);
double calculateSurcharge(double fee, int urgency);
int findAvailableBed(int wardIndex);
double calculateWardCost(int wardIndex, int days);
void calculateBill(int index);
double calculateDiscount(double gross, int age);
void patientPriority(void);
void displayPatientPriority(void);
void generateReport(void);
void displayPatientBill(int index);

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
        
        switch (choice) {
            case 1:
                displaySpecialties();
                break;
                
            case 2:
                displayWards();
                break;
                
            case 3:
                displayBedOccupancy();
                break;
                
            case 4:
                registerPatient();
                break;
                
            case 5:
                displayPatientPriority();
                break;
                
            case 6:
                generateReport();
                break;
                
            case 7:
                printf("\nExiting Smart Hospital System...\n");
                break;
                
            default:
                printf("\nInvalid choice. Please select correct choice from main menu.\n");
        }
    } while (choice != 7);
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
    printf("7. Exit\n");
    printf("====================================================\n");
}

void displaySpecialties(void)
{
    int i;

    printf("\n----------------------------------------------------\n");
    printf("DOCTOR SPECIALTIES\n");
    printf("----------------------------------------------------\n");
    printf("%-5s %-25s %-15s %-15s %-10s\n","ID", "Specialty", "Fee", "Time", "Daily Cap");

    for (i = 0; i < SPECIALTIES_NUM; i++) {
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
    printf("%-5s %-30s %-15s %-10s\n","ID", "Ward", "Daily Rate", "Capacity");

    for (i = 0; i < WARDS_NUM; i++) {
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

    for (i = 0; i < WARDS_NUM; i++) {
        printf("\nWard %d: %s\n", i + 1, wardName[i]);

        for (j = 0; j < bedCapacity[i]; j++) {
            if (bedOccupancy[i][j] == 0) {
                printf("Bed %02d: Available   ", j + 1);
            }
            else {
                printf("Bed %02d: Occupied   ", j + 1);
            }

            if ((j + 1) % 2 == 0) {
                printf("\n");
            }
        }

        printf("\n");
    }
}

void registerPatient(void)
{
    int index;
    int specialtyChoice;
    int wardChoice;

    if (patientCount >= MAX_PATIENTS) {
        printf("\nPatient storage is full.\n");
        return;
    }

    index = patientCount;

    printf("\n====================================================\n");
    printf("              PATIENT REGISTRATION\n");
    printf("====================================================\n");

    patientId[index] = 1001 + index;

    printf("Patient Name: ");
    scanf(" %[^\n]", patientName[index]);

    printf("Patient Age: ");
    scanf("%d", &patientAge[index]);

    do {
        printf("\nUrgency Level:\n");
        printf("1. Normal\n");
        printf("2. Urgent\n");
        printf("3. Critical\n");
        printf("Enter urgency level: ");
        scanf("%d", &emergencyLevel[index]);

    } while (emergencyLevel[index] < 1 ||
             emergencyLevel[index] > 3);


    displaySpecialties();

    do {
        printf("\nSelect Specialty ID (1-4): ");
        scanf("%d", &specialtyChoice);

    } while (specialtyChoice < 1 || specialtyChoice > SPECIALTIES_NUM);
    patientSpecialty[index] = specialtyChoice;
    
    waitingTime[index] = calculateWaitingTime(specialtyChoice - 1);
    specialtyQueue[specialtyChoice - 1]++;

    printf("\nIs the patient admitted to a ward?\n");
    printf("1. Yes\n");
    printf("0. No\n");
    printf("Enter choice: ");
    scanf("%d", &wardAdmission[index]);
    
    if (wardAdmission[index] == 1) {
        displayWards();

        do {
            printf("\nEnter Ward ID (1-4): ");
            scanf("%d", &wardChoice);

        } while (wardChoice < 1 ||
                 wardChoice > WARDS_NUM);

        patientWard[index] = wardChoice;

        printf("Enter number of days admitted: ");
        scanf("%d", &daysAdmitted[index]);

        assignBed(index);
    }
    else {
        patientWard[index] = 0;
        daysAdmitted[index] = 0;
        assignedBed[index] = 0;
    }
    
    
    calculateBill(index);
    printf("\nPatient successfully registered.\n");
    displayPatientBill(index);
    patientCount++;
}

double calculateWaitingTime(int specialtyIndex)
{
    return specialtyQueue[specialtyIndex] * consultationTime[specialtyIndex];
}

double calculateSurcharge(double fee, int urgency) {
    if (urgency == 1) {
        return 0.0;
    }
    else if (urgency == 2) {
        return fee * 0.20;
    }
    else if (urgency == 3) {
        return fee * 0.50;
    }
    return 0.0;
}

int findAvailableBed(int wardIndex)
{
    int i;

    for (i = 0; i < bedCapacity[wardIndex]; i++) {
        if (bedOccupancy[wardIndex][i] == 0) {
            return i;
        }
    }
    return -1;
}

void assignBed(int patientIndex)
{
    int wardIndex;
    int bedIndex;

    wardIndex = patientWard[patientIndex] - 1;

    bedIndex = findAvailableBed(wardIndex);

    if (bedIndex == -1) {
        printf("\nNo beds are available in this ward.\n");
        patientWard[patientIndex] = 0;
        wardAdmission[patientIndex] = 0;
        assignedBed[patientIndex] = 0;
        daysAdmitted[patientIndex] = 0;
        return;
    }

    bedOccupancy[wardIndex][bedIndex] = 1;

    assignedBed[patientIndex] = bedIndex + 1;

    printf("\nBed successfully assigned.\n");
    printf("Ward: %s\n", wardName[wardIndex]);
    printf("Bed: #%02d\n", assignedBed[patientIndex]);
}

double calculateWardCost(int wardIndex, int days)
{
    if (wardIndex < 0 || days <= 0) {
        return 0.0;
    }
    return days * dailyBedRate[wardIndex];
}

void calculateBill(int index)
{
    int specialtyIndex;
    int wardIndex;

    specialtyIndex = patientSpecialty[index] - 1;
    baseFee[index] = consultationFee[specialtyIndex];
    emergencySurcharge[index] = calculateSurcharge(baseFee[index], emergencyLevel[index]);

    if (wardAdmission[index] == 1) {
        wardIndex = patientWard[index] - 1;
        wardCost[index] = calculateWardCost(wardIndex, daysAdmitted[index]);
    }
    else {
        wardCost[index] = 0.0;
    }

    grossTotal[index] = baseFee[index] + emergencySurcharge[index] + wardCost[index];
    discount[index] = calculateDiscount(grossTotal[index], patientAge[index]);
    finalPayable[index] = grossTotal[index] - discount[index];
}

double calculateDiscount(double gross, int age)
{
    if (age < 5 || age > 65) {
        return gross * 0.15;
    }
return 0.0;
}

void patientPriority(void)
{
    int order[MAX_PATIENTS];
    int i;
    int j;
    int temp;

    for (i = 0; i < patientCount; i++) {
        order[i] = i;
    }

    for (i = 0; i < patientCount - 1; i++) {
        for (j = i + 1; j < patientCount; j++) {
            if (emergencyLevel[order[j]] > emergencyLevel[order[i]]) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
    
    printf("\n====================================================\n");
    printf("          PATIENT PRIORITY\n");
    printf("====================================================\n");

    for (i = 0; i < patientCount; i++) {
        printf("%d. PAT-%d | %-20s | Level %d\n",
               i + 1,
               patientId[order[i]],
               patientName[order[i]],
               emergencyLevel[order[i]]);
    }
}

void displayPatientPriority(void)
{
    if (patientCount == 0){
        printf("\nNo patients registered yet.\n");
        return;
    }
    patientPriority();
}

void generateReport(void)
{
    int i;
    int urgency1 = 0;
    int urgency2 = 0;
    int urgency3 = 0;
    
    double totalRevenue = 0.0;
    double totalDiscount = 0.0;
    
    int highestPatient = 0;
    
    printf("\n====================================================\n");
    printf("             PERFORMANCE REPORT\n");
    printf("====================================================\n");
    
    for (i = 0; i < patientCount; i++) {
        if (emergencyLevel[i] == 1) {
            urgency1++;
        }
        else if (emergencyLevel[i] == 2) {
            urgency2++;
        }
        else if (emergencyLevel[i] == 3) {
            urgency3++;
        }
        
        totalRevenue += finalPayable[i];
        totalDiscount += discount[i];
        
        if (finalPayable[i] > finalPayable[highestPatient]) {
            highestPatient = i;
        }
    }
    
    printf("\nTotal Patients Registered: %d\n", patientCount);
    printf("\nPatients by Urgency:\n");
    printf("Level 1 - Normal  : %d\n", urgency1);
    printf("Level 2 - Urgent  : %d\n", urgency2);
    printf("Level 3 - Critical: %d\n", urgency3);
    
    printf("\nFinancial Summary:\n");
    printf("Total Revenue     : LKR %.2f\n", totalRevenue);
    printf("Total Discounts   : LKR %.2f\n", totalDiscount);
    printf("\nBed Occupancy:\n");
    
    for (i = 0; i < WARDS_NUM; i++) {
        int j;
        int occupied = 0;
        
        for (j = 0; j < bedCapacity[i]; j++) {
            if (bedOccupancy[i][j] == 1) {
                occupied++;
            }
        }
        
        printf("%-30s : %.2f%%\n", wardName[i], ((double)occupied /bedCapacity[i]) * 100);
    }
    
    
    if (patientCount > 0) {
        printf("\nHighest-Paying Patient:\n");
        printf("Name       : %s\n", patientName[highestPatient]);
        printf("Patient ID : PAT-%d\n", patientId[highestPatient]);
        printf("Final Bill : LKR %.2f\n", finalPayable[highestPatient]);
    }
}

void displayPatientBill(int index)
{
    printf("\n====================================================\n");
    printf("          SMART HOSPITAL ADMISSION & BILL\n");
    printf("====================================================\n");
    
    printf("Patient ID       : PAT-%d\n", patientId[index]);
    printf("Patient Name     : %s\n", patientName[index]);
    printf("Age              : %d Years", patientAge[index]);
    
    if (patientAge[index] < 5 || patientAge[index] > 65) {
        printf(" (15%% Subsidy Eligible)");
    }
    printf("\n");
    printf("Specialty        : %s\n", specialtyName[patientSpecialty[index] - 1]);
    
    if (wardAdmission[index] == 1) {
        printf("Assigned Ward    : %s\n", wardName[patientWard[index] - 1]);
        printf("Assigned Bed     : #%02d\n",assignedBed[index]);
    }
    else {
        printf("Assigned Ward    : Outpatient / OPD\n");
    }
    
    printf("Urgency Level    : ");
    
    if (emergencyLevel[index] == 1) {
        printf("Level 1 (Normal)\n");
    }
    else if (emergencyLevel[index] == 2) {
        printf("Level 2 (Urgent)\n");
    }
    else {
        printf("Level 3 (Critical)\n");
    }
    
    printf("----------------------------------------------------\n");
    printf("Base Consultation Fee : LKR %.2f\n", baseFee[index]);
    printf("Emergency Surcharge   : LKR %.2f\n", emergencySurcharge[index]);
    printf("Ward Stay Cost        : LKR %.2f\n",wardCost[index]);
    printf("----------------------------------------------------\n");
    printf("Gross Total Bill      : LKR %.2f\n", grossTotal[index]);
    printf("Age Subsidy Discount  : LKR -%.2f\n", discount[index]);
    printf("----------------------------------------------------\n");
    printf("Final Payable Amount  : LKR %.2f\n", finalPayable[index]);
    printf("Estimated Waiting Time: %.2f mins\n",waitingTime[index]);
    printf("====================================================\n");
}
