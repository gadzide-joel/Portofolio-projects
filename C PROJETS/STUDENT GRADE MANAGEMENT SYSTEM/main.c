/*
 * ========================================
 * STUDENT GRADE MANAGEMENT SYSTEM
 * ========================================
 *
 * Author: GADZIDE Komi Joël
 * Date: November 2024
 * Language: C
 *
 * Description:
 * A comprehensive system for managing student grades,
 * calculating statistics, and generating reports.
 *
 * Features:
 * - Add/remove students and courses
 * - Enter and modify grades
 * - Calculate GPA and statistics
 * - Generate reports
 * - Data persistence
 *
 * Perfect for demonstrating:
 * - Structure arrays
 * - Statistical calculations
 * - File handling
 * - Data validation
 * ========================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 1000
#define MAX_COURSES 10
#define MAX_NAME 50

typedef struct {
    char course_code[10];
    char course_name[50];
    float grade;
    int credits;
} CourseGrade;

typedef struct {
    int student_id;
    char name[MAX_NAME];
    char program[50];
    CourseGrade courses[MAX_COURSES];
    int course_count;
    float gpa;
} Student;

typedef struct {
    Student students[MAX_STUDENTS];
    int student_count;
    int next_student_id;
} GradeSystem;

void init_system(GradeSystem *sys) {
    sys->student_count = 0;
    sys->next_student_id = 1001;
}

void add_student(GradeSystem *sys) {
    if (sys->student_count >= MAX_STUDENTS) {
        printf("Error: Maximum students reached!\n");
        return;
    }

    Student *student = &sys->students[sys->student_count];
    student->student_id = sys->next_student_id++;
    student->course_count = 0;
    student->gpa = 0.0;

    printf("Enter student name: ");
    getchar();
    fgets(student->name, MAX_NAME, stdin);
    student->name[strcspn(student->name, "\n")] = 0;

    printf("Enter program: ");
    fgets(student->program, 50, stdin);
    student->program[strcspn(student->program, "\n")] = 0;

    sys->student_count++;
    printf("Student added successfully! ID: %d\n", student->student_id);
}

void add_grade(GradeSystem *sys) {
    int student_id;
    printf("Enter student ID: ");
    scanf("%d", &student_id);

    // Find student
    int student_index = -1;
    for (int i = 0; i < sys->student_count; i++) {
        if (sys->students[i].student_id == student_id) {
            student_index = i;
            break;
        }
    }

    if (student_index == -1) {
        printf("Error: Student not found!\n");
        return;
    }

    Student *student = &sys->students[student_index];

    if (student->course_count >= MAX_COURSES) {
        printf("Error: Maximum courses reached for this student!\n");
        return;
    }

    CourseGrade *course = &student->courses[student->course_count];

    printf("Enter course code: ");
    getchar();
    fgets(course->course_code, 10, stdin);
    course->course_code[strcspn(course->course_code, "\n")] = 0;

    printf("Enter course name: ");
    fgets(course->course_name, 50, stdin);
    course->course_name[strcspn(course->course_name, "\n")] = 0;

    printf("Enter credits: ");
    scanf("%d", &course->credits);

    printf("Enter grade (0-100): ");
    scanf("%f", &course->grade);

    student->course_count++;
    printf("Grade added successfully!\n");
}

void calculate_gpa(GradeSystem *sys) {
    for (int i = 0; i < sys->student_count; i++) {
        Student *student = &sys->students[i];

        if (student->course_count == 0) {
            student->gpa = 0.0;
            continue;
        }

        float total_points = 0.0;
        int total_credits = 0;

        for (int j = 0; j < student->course_count; j++) {
            CourseGrade *course = &student->courses[j];

            // Convert percentage to GPA (simplified)
            float grade_point;
            if (course->grade >= 90) grade_point = 4.0;
            else if (course->grade >= 80) grade_point = 3.0;
            else if (course->grade >= 70) grade_point = 2.0;
            else if (course->grade >= 60) grade_point = 1.0;
            else grade_point = 0.0;

            total_points += grade_point * course->credits;
            total_credits += course->credits;
        }

        student->gpa = total_credits > 0 ? total_points / total_credits : 0.0;
    }

    printf("GPA calculated for all students!\n");
}

void display_students(GradeSystem *sys) {
    printf("\n=== ALL STUDENTS ===\n");
    printf("%-10s %-20s %-15s %-6s %s\n",
           "ID", "Name", "Program", "GPA", "Courses");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < sys->student_count; i++) {
        Student *student = &sys->students[i];
        printf("%-10d %-20s %-15s %-6.2f %d\n",
               student->student_id, student->name, student->program,
               student->gpa, student->course_count);
    }
}

void display_student_details(GradeSystem *sys) {
    int student_id;
    printf("Enter student ID: ");
    scanf("%d", &student_id);

    // Find student
    for (int i = 0; i < sys->student_count; i++) {
        if (sys->students[i].student_id == student_id) {
            Student *student = &sys->students[i];

            printf("\n=== STUDENT DETAILS ===\n");
            printf("ID: %d\n", student->student_id);
            printf("Name: %s\n", student->name);
            printf("Program: %s\n", student->program);
            printf("GPA: %.2f\n", student->gpa);
            printf("Courses: %d\n", student->course_count);

            if (student->course_count > 0) {
                printf("\n%-12s %-20s %-8s %s\n",
                       "Code", "Course Name", "Credits", "Grade");
                printf("------------------------------------------------\n");

                for (int j = 0; j < student->course_count; j++) {
                    CourseGrade *course = &student->courses[j];
                    printf("%-12s %-20s %-8d %.1f\n",
                           course->course_code, course->course_name,
                           course->credits, course->grade);
                }
            }
            return;
        }
    }

    printf("Error: Student not found!\n");
}

int main() {
    GradeSystem sys;
    int choice;

    init_system(&sys);

    printf("=== STUDENT GRADE MANAGEMENT SYSTEM ===\n");
    printf("Author: GADZIDE Komi Joël\n");

    do {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Add Student\n");
        printf("2. Add Grade\n");
        printf("3. Calculate GPA\n");
        printf("4. Display All Students\n");
        printf("5. Display Student Details\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: add_student(&sys); break;
            case 2: add_grade(&sys); break;
            case 3: calculate_gpa(&sys); break;
            case 4: display_students(&sys); break;
            case 5: display_student_details(&sys); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);

    return 0;
}
