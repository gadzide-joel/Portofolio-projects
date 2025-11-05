/*
 * ========================================
 * UTILITY FUNCTIONS MODULE
 * ========================================
 */

#include "hospital.h"

/* ========================================
 * GET CURRENT DATE
 * ======================================== */
Date get_current_date(void) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    Date current_date;
    current_date.day = tm_info->tm_mday;
    current_date.month = tm_info->tm_mon + 1;
    current_date.year = tm_info->tm_year + 1900;

    return current_date;
}

/* ========================================
 * VALIDATE DATE
 * ======================================== */
int is_valid_date(Date date) {
    // Basic validation
    if (date.year < 2020 || date.year > 2030) return 0;
    if (date.month < 1 || date.month > 12) return 0;
    if (date.day < 1 || date.day > 31) return 0;

    // Validate months with 30 days
    if ((date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) &&
        date.day > 30) return 0;

    // Validate February
    if (date.month == 2) {
        // Simplified leap year
        int is_leap = (date.year % 4 == 0);
        if (is_leap && date.day > 29) return 0;
        if (!is_leap && date.day > 28) return 0;
    }

    return 1;
}

/* ========================================
 * VALIDATE TIME
 * ======================================== */
int is_valid_time(Time time) {
    return (time.hour >= 0 && time.hour <= 23 &&
            time.minute >= 0 && time.minute <= 59);
}

/* ========================================
 * CLEAR INPUT BUFFER
 * ======================================== */
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* ========================================
 * DISPLAY MAIN MENU
 * ======================================== */
void display_main_menu(void) {
    printf("\n=== HOSPITAL MANAGEMENT SYSTEM ===\n");
    printf("1. Patient Management\n");
    printf("2. Doctor Management\n");
    printf("3. Appointment Management\n");
    printf("4. System Overview\n");
    printf("0. Exit\n");
    printf("Choose an option: ");
}

/* ========================================
 * DISPLAY PATIENT MENU
 * ======================================== */
void display_patient_menu(void) {
    printf("\n=== PATIENT MANAGEMENT ===\n");
    printf("1. Add Patient\n");
    printf("2. Display All Patients\n");
    printf("3. Find Patient\n");
    printf("4. Return to Main Menu\n");
    printf("Choose an option: ");
}

/* ========================================
 * DISPLAY DOCTOR MENU
 * ======================================== */
void display_doctor_menu(void) {
    printf("\n=== DOCTOR MANAGEMENT ===\n");
    printf("1. Add Doctor\n");
    printf("2. Display All Doctors\n");
    printf("3. Display by Specialization\n");
    printf("4. Return to Main Menu\n");
    printf("Choose an option: ");
}

/* ========================================
 * DISPLAY APPOINTMENT MENU
 * ======================================== */
void display_appointment_menu(void) {
    printf("\n=== APPOINTMENT MANAGEMENT ===\n");
    printf("1. Schedule Appointment\n");
    printf("2. Display All Appointments\n");
    printf("3. Cancel Appointment\n");
    printf("4. Return to Main Menu\n");
    printf("Choose an option: ");
}
