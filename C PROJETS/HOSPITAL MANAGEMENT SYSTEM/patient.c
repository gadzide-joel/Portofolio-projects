/*
 * ========================================
 * PATIENT MANAGEMENT MODULE
 * ========================================
 */

#include "hospital.h"

/* ========================================
 * ADD NEW PATIENT
 * ======================================== */
void add_patient(HospitalSystem *hospital) {
    if (hospital->patient_count >= MAX_PATIENTS) {
        printf("Error: Maximum number of patients reached!\n");
        return;
    }

    Patient *patient = &hospital->patients[hospital->patient_count];
    patient->patient_id = hospital->next_patient_id++;

    printf("\n=== NEW PATIENT ===\n");

    printf("Full name: ");
    clear_input_buffer();
    fgets(patient->name, MAX_NAME, stdin);
    patient->name[strcspn(patient->name, "\n")] = 0;

    printf("Age: ");
    scanf("%d", &patient->age);

    printf("Gender (M/F): ");
    scanf("%s", patient->gender);

    printf("Blood type: ");
    scanf("%s", patient->blood_type);

    printf("Address: ");
    clear_input_buffer();
    fgets(patient->address, 100, stdin);
    patient->address[strcspn(patient->address, "\n")] = 0;

    printf("Phone: ");
    fgets(patient->phone, 15, stdin);
    patient->phone[strcspn(patient->phone, "\n")] = 0;

    // Current registration date
    patient->registration_date = get_current_date();

    hospital->patient_count++;

    printf("Patient added successfully! ID: %d\n", patient->patient_id);
}

/* ========================================
 * DISPLAY ALL PATIENTS
 * ======================================== */
void display_patients(HospitalSystem *hospital) {
    printf("\n=== PATIENT LIST (%d) ===\n", hospital->patient_count);

    if (hospital->patient_count == 0) {
        printf("No patients registered.\n");
        return;
    }

    printf("%-10s %-20s %-5s %-6s %-8s %-15s %s\n",
           "ID", "Name", "Age", "Gender", "Blood", "Phone", "Reg Date");
    printf("----------------------------------------------------------------------------\n");

    for (int i = 0; i < hospital->patient_count; i++) {
        Patient *patient = &hospital->patients[i];
        printf("%-10d %-20s %-5d %-6s %-8s %-15s %02d/%02d/%d\n",
               patient->patient_id, patient->name, patient->age,
               patient->gender, patient->blood_type, patient->phone,
               patient->registration_date.day,
               patient->registration_date.month,
               patient->registration_date.year);
    }
}

/* ========================================
 * FIND PATIENT BY ID
 * ======================================== */
Patient* find_patient(HospitalSystem *hospital, int patient_id) {
    for (int i = 0; i < hospital->patient_count; i++) {
        if (hospital->patients[i].patient_id == patient_id) {
            return &hospital->patients[i];
        }
    }
    return NULL;
}

/* ========================================
 * DISPLAY PATIENT DETAILS
 * ======================================== */
void display_patient_details(HospitalSystem *hospital, int patient_id) {
    Patient *patient = find_patient(hospital, patient_id);

    if (patient == NULL) {
        printf("Patient not found!\n");
        return;
    }

    printf("\n=== PATIENT RECORD ===\n");
    printf("ID: %d\n", patient->patient_id);
    printf("Name: %s\n", patient->name);
    printf("Age: %d years\n", patient->age);
    printf("Gender: %s\n", patient->gender);
    printf("Blood type: %s\n", patient->blood_type);
    printf("Address: %s\n", patient->address);
    printf("Phone: %s\n", patient->phone);
    printf("Registration date: %02d/%02d/%d\n",
           patient->registration_date.day,
           patient->registration_date.month,
           patient->registration_date.year);
}
