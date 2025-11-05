/*
 * ========================================
 * DOCTOR MANAGEMENT MODULE
 * ========================================
 */

#include "hospital.h"

/* ========================================
 * ADD NEW DOCTOR
 * ======================================== */
void add_doctor(HospitalSystem *hospital) {
    if (hospital->doctor_count >= MAX_DOCTORS) {
        printf("Error: Maximum number of doctors reached!\n");
        return;
    }

    Doctor *doctor = &hospital->doctors[hospital->doctor_count];
    doctor->doctor_id = hospital->next_doctor_id++;
    doctor->available = 1;

    printf("\n=== NEW DOCTOR ===\n");

    printf("Doctor name: ");
    clear_input_buffer();
    fgets(doctor->name, MAX_NAME, stdin);
    doctor->name[strcspn(doctor->name, "\n")] = 0;

    printf("Specialization: ");
    fgets(doctor->specialization, 50, stdin);
    doctor->specialization[strcspn(doctor->specialization, "\n")] = 0;

    printf("Phone: ");
    fgets(doctor->phone, 15, stdin);
    doctor->phone[strcspn(doctor->phone, "\n")] = 0;

    hospital->doctor_count++;

    printf("Doctor added successfully! ID: %d\n", doctor->doctor_id);
}

/* ========================================
 * DISPLAY ALL DOCTORS
 * ======================================== */
void display_doctors(HospitalSystem *hospital) {
    printf("\n=== DOCTOR LIST (%d) ===\n", hospital->doctor_count);

    if (hospital->doctor_count == 0) {
        printf("No doctors registered.\n");
        return;
    }

    printf("%-10s %-20s %-20s %-15s %s\n",
           "ID", "Name", "Specialization", "Phone", "Status");
    printf("----------------------------------------------------------------\n");

    for (int i = 0; i < hospital->doctor_count; i++) {
        Doctor *doctor = &hospital->doctors[i];
        printf("%-10d %-20s %-20s %-15s %s\n",
               doctor->doctor_id, doctor->name, doctor->specialization,
               doctor->phone, doctor->available ? "Available" : "Busy");
    }
}

/* ========================================
 * FIND DOCTOR BY ID
 * ======================================== */
Doctor* find_doctor(HospitalSystem *hospital, int doctor_id) {
    for (int i = 0; i < hospital->doctor_count; i++) {
        if (hospital->doctors[i].doctor_id == doctor_id) {
            return &hospital->doctors[i];
        }
    }
    return NULL;
}

/* ========================================
 * DISPLAY DOCTORS BY SPECIALIZATION
 * ======================================== */
void display_doctors_by_specialization(HospitalSystem *hospital, const char* specialization) {
    printf("\n=== DOCTORS - %s ===\n", specialization);

    int found = 0;
    for (int i = 0; i < hospital->doctor_count; i++) {
        Doctor *doctor = &hospital->doctors[i];
        if (strcmp(doctor->specialization, specialization) == 0) {
            printf("ID: %d, Name: %s, Phone: %s, Status: %s\n",
                   doctor->doctor_id, doctor->name, doctor->phone,
                   doctor->available ? "Available" : "Busy");
            found = 1;
        }
    }

    if (!found) {
        printf("No doctors found in this specialization.\n");
    }
}
