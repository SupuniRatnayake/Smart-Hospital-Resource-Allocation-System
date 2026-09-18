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
    
    return 0;
}

