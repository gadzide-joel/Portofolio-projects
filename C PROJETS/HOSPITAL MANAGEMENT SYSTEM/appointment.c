/*
 * ========================================
 * APPOINTMENT MANAGEMENT MODULE
 * ========================================
 */

#include "hospital.h"

/* ========================================
 * SCHEDULE APPOINTMENT
 * ======================================== */
void schedule_appointment(HospitalSystem *hospital) {
    if (hospital->appointment_count >= MAX_APPOINTMENTS) {
        printf("Error: Maximum number of appointments reached!\n");
        return;
    }

    Appointment *appointment = &hospital->appointments[hospital->appointment_count];
    appointment->appointment_id = hospital->next_appointment_id++;

    printf("\n=== NEW APPOINTMENT ===\n");

    // Input patient ID
    printf("Patient ID: ");
    scanf("%d", &appointment->patient_id);

    Patient *patient = find_patient(hospital, appointment->patient_id);
    if (patient == NULL) {
        printf("Patient not found!\n");
        return;
    }

    // Input doctor ID
    printf("Doctor ID: ");
    scanf("%d", &appointment->doctor_id);

    Doctor *doctor = find_doctor(hospital, appointment->doctor_id);
    if (doctor == NULL) {
        printf("Doctor not found!\n");
        return;
    }

    if (!doctor->available) {
        printf("This doctor is not available!\n");
        return;
    }

    // Input date
    printf("Appointment date (DD MM YYYY): ");
    scanf("%d %d %d", &appointment->date.day,
                       &appointment->date.month,
                       &appointment->date.year);

    if (!is_valid_date(appointment->date)) {
        printf("Invalid date!\n");
        return;
    }

    // Input time
    printf("Appointment time (HH MM): ");
    scanf("%d %d", &appointment->time.hour, &appointment->time.minute);

    if (!is_valid_time(appointment->time)) {
        printf("Invalid time!\n");
        return;
    }

    // Visit reason
    printf("Consultation reason: ");
    clear_input_buffer();
    fgets(appointment->reason, 100, stdin);
    appointment->reason[strcspn(appointment->reason, "\n")] = 0;

    strcpy(appointment->status, "SCHEDULED");

    hospital->appointment_count++;

    printf("Appointment scheduled successfully! ID: %d\n", appointment->appointment_id);
    printf("Patient: %s\n", patient->name);
    printf("Doctor: %s (%s)\n", doctor->name, doctor->specialization);
    printf("Date: %02d/%02d/%d at %02d:%02d\n",
           appointment->date.day, appointment->date.month, appointment->date.year,
           appointment->time.hour, appointment->time.minute);
}

/* ========================================
 * DISPLAY ALL APPOINTMENTS
 * ======================================== */
void display_appointments(HospitalSystem *hospital) {
    printf("\n=== APPOINTMENT LIST (%d) ===\n", hospital->appointment_count);

    if (hospital->appointment_count == 0) {
        printf("No appointments scheduled.\n");
        return;
    }

    printf("%-12s %-20s %-20s %-12s %-8s %-20s %s\n",
           "Appointment ID", "Patient", "Doctor", "Date", "Time", "Reason", "Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < hospital->appointment_count; i++) {
        Appointment *appointment = &hospital->appointments[i];

        // Find patient name
        char patient_name[MAX_NAME] = "Unknown";
        Patient *patient = find_patient(hospital, appointment->patient_id);
        if (patient != NULL) {
            strcpy(patient_name, patient->name);
        }

        // Find doctor name
        char doctor_name[MAX_NAME] = "Unknown";
        Doctor *doctor = find_doctor(hospital, appointment->doctor_id);
        if (doctor != NULL) {
            strcpy(doctor_name, doctor->name);
        }

        printf("%-12d %-20s %-20s %02d/%02d/%d  %02d:%02d   %-20s %s\n",
               appointment->appointment_id,
               patient_name,
               doctor_name,
               appointment->date.day,
               appointment->date.month,
               appointment->date.year,
               appointment->time.hour,
               appointment->time.minute,
               appointment->reason,
               appointment->status);
    }
}

/* ========================================
 * CANCEL APPOINTMENT
 * ======================================== */
void cancel_appointment(HospitalSystem *hospital, int appointment_id) {
    for (int i = 0; i < hospital->appointment_count; i++) {
        if (hospital->appointments[i].appointment_id == appointment_id) {
            strcpy(hospital->appointments[i].status, "CANCELLED");
            printf("Appointment %d cancelled successfully!\n", appointment_id);
            return;
        }
    }
    printf("Appointment not found!\n");
}
