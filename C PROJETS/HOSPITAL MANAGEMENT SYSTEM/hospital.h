/*
 * ========================================
 * HOSPITAL MANAGEMENT SYSTEM - HEADER FILE
 * ========================================
 *
 * Author: GADZIDE Komi Joel
 * Date: November 2024
 * Language: C
 */

#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PATIENTS 1000
#define MAX_DOCTORS 100
#define MAX_APPOINTMENTS 5000
#define MAX_NAME 50

/* ========================================
 * DATA STRUCTURES
 * ======================================== */

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int hour, minute;
} Time;

typedef struct {
    int doctor_id;
    char name[MAX_NAME];
    char specialization[50];
    char phone[15];
    int available;
} Doctor;

typedef struct {
    int patient_id;
    char name[MAX_NAME];
    int age;
    char gender[10];
    char address[100];
    char phone[15];
    char blood_type[5];
    Date registration_date;
} Patient;

typedef struct {
    int appointment_id;
    int patient_id;
    int doctor_id;
    Date date;
    Time time;
    char reason[100];
    char status[20];
} Appointment;

typedef struct {
    Patient patients[MAX_PATIENTS];
    Doctor doctors[MAX_DOCTORS];
    Appointment appointments[MAX_APPOINTMENTS];
    int patient_count;
    int doctor_count;
    int appointment_count;
    int next_patient_id;
    int next_doctor_id;
    int next_appointment_id;
} HospitalSystem;

/* ========================================
 * FUNCTION PROTOTYPES
 * ======================================== */

// Initialization functions
void init_hospital(HospitalSystem *hospital);
void add_sample_doctors(HospitalSystem *hospital);

// Patient functions
void add_patient(HospitalSystem *hospital);
void display_patients(HospitalSystem *hospital);
Patient* find_patient(HospitalSystem *hospital, int patient_id);
void display_patient_details(HospitalSystem *hospital, int patient_id);

// Doctor functions
void add_doctor(HospitalSystem *hospital);
void display_doctors(HospitalSystem *hospital);
Doctor* find_doctor(HospitalSystem *hospital, int doctor_id);
void display_doctors_by_specialization(HospitalSystem *hospital, const char* specialization);

// Appointment functions
void schedule_appointment(HospitalSystem *hospital);
void display_appointments(HospitalSystem *hospital);
void cancel_appointment(HospitalSystem *hospital, int appointment_id);

// Utility functions
Date get_current_date(void);
int is_valid_date(Date date);
int is_valid_time(Time time);
void clear_input_buffer(void);

// Menu functions
void display_main_menu(void);
void display_patient_menu(void);
void display_doctor_menu(void);
void display_appointment_menu(void);
void display_overview(HospitalSystem *hospital);

// Menu handlers
void handle_patient_menu(HospitalSystem *hospital);
void handle_doctor_menu(HospitalSystem *hospital);
void handle_appointment_menu(HospitalSystem *hospital);

#endif /* HOSPITAL_H */
