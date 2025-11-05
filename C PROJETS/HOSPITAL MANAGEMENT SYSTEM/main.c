/*
 * ========================================
 * HOSPITAL MANAGEMENT SYSTEM - MAIN PROGRAM
 * ========================================
 *
 * Author: GADZIDE Komi Joel
 * Date: November 2024
 * Language: C
 *
 * CSC Scholarship Portfolio Project
 */

#include "hospital.h"

/* ========================================
 * INITIALIZATION FUNCTION
 * ======================================== */
void init_hospital(HospitalSystem *hospital) {
    hospital->patient_count = 0;
    hospital->doctor_count = 0;
    hospital->appointment_count = 0;
    hospital->next_patient_id = 1001;
    hospital->next_doctor_id = 2001;
    hospital->next_appointment_id = 3001;

    // Add default doctors for testing
    add_sample_doctors(hospital);
}

/* ========================================
 * ADD SAMPLE DOCTORS
 * ======================================== */
void add_sample_doctors(HospitalSystem *hospital) {
    // Doctor 1
    Doctor *doc1 = &hospital->doctors[hospital->doctor_count++];
    doc1->doctor_id = hospital->next_doctor_id++;
    strcpy(doc1->name, "Dr. Sarah Johnson");
    strcpy(doc1->specialization, "Cardiology");
    strcpy(doc1->phone, "555-0101");
    doc1->available = 1;

    // Doctor 2
    Doctor *doc2 = &hospital->doctors[hospital->doctor_count++];
    doc2->doctor_id = hospital->next_doctor_id++;
    strcpy(doc2->name, "Dr. Michael Chen");
    strcpy(doc2->specialization, "Pediatrics");
    strcpy(doc2->phone, "555-0102");
    doc2->available = 1;

    // Doctor 3
    Doctor *doc3 = &hospital->doctors[hospital->doctor_count++];
    doc3->doctor_id = hospital->next_doctor_id++;
    strcpy(doc3->name, "Dr. Maria Rodriguez");
    strcpy(doc3->specialization, "Dermatology");
    strcpy(doc3->phone, "555-0103");
    doc3->available = 1;
}

/* ========================================
 * SYSTEM OVERVIEW
 * ======================================== */
void display_overview(HospitalSystem *hospital) {
    printf("\n=== SYSTEM OVERVIEW ===\n");
    printf("System Statistics:\n");
    printf("   Patients: %d\n", hospital->patient_count);
    printf("   Doctors: %d\n", hospital->doctor_count);
    printf("   Appointments: %d\n", hospital->appointment_count);

    // Available doctors
    int available_doctors = 0;
    for (int i = 0; i < hospital->doctor_count; i++) {
        if (hospital->doctors[i].available) {
            available_doctors++;
        }
    }
    printf("   Available doctors: %d/%d\n", available_doctors, hospital->doctor_count);
}

/* ========================================
 * PATIENT MENU HANDLER
 * ======================================== */
void handle_patient_menu(HospitalSystem *hospital) {
    int choice;

    do {
        display_patient_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_patient(hospital);
                break;
            case 2:
                display_patients(hospital);
                break;
            case 3:
                {
                    int patient_id;
                    printf("Patient ID to search: ");
                    scanf("%d", &patient_id);
                    display_patient_details(hospital, patient_id);
                }
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (choice != 4);
}

/* ========================================
 * DOCTOR MENU HANDLER
 * ======================================== */
void handle_doctor_menu(HospitalSystem *hospital) {
    int choice;

    do {
        display_doctor_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                add_doctor(hospital);
                break;
            case 2:
                display_doctors(hospital);
                break;
            case 3:
                {
                    char specialization[50];
                    printf("Specialization to search: ");
                    clear_input_buffer();
                    fgets(specialization, 50, stdin);
                    specialization[strcspn(specialization, "\n")] = 0;
                    display_doctors_by_specialization(hospital, specialization);
                }
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (choice != 4);
}

/* ========================================
 * APPOINTMENT MENU HANDLER
 * ======================================== */
void handle_appointment_menu(HospitalSystem *hospital) {
    int choice;

    do {
        display_appointment_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                schedule_appointment(hospital);
                break;
            case 2:
                display_appointments(hospital);
                break;
            case 3:
                {
                    int appointment_id;
                    printf("Appointment ID to cancel: ");
                    scanf("%d", &appointment_id);
                    cancel_appointment(hospital, appointment_id);
                }
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid option!\n");
        }
    } while (choice != 4);
}

/* ========================================
 * MAIN FUNCTION
 * ======================================== */
int main() {
    HospitalSystem hospital;
    int choice;

    // System initialization
    init_hospital(&hospital);

    printf("========================================\n");
    printf("   HOSPITAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("Author: GADZIDE Komi Joel\n");
    printf("========================================\n");

    // Main loop
    do {
        display_main_menu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                handle_patient_menu(&hospital);
                break;
            case 2:
                handle_doctor_menu(&hospital);
                break;
            case 3:
                handle_appointment_menu(&hospital);
                break;
            case 4:
                display_overview(&hospital);
                break;
            case 0:
                printf("\nThank you for using the system!\n");
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
