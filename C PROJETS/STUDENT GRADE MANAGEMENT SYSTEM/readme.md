#  STUDENT GRADE MANAGEMENT SYSTEM
* ========================================

* Author: GADZIDE Komi Joël
* Date: November 2024
* Language: C

# Description:
* A comprehensive academic management system that handles student records,
* course grades, GPA calculations, and academic reporting for educational
* institutions.

# Features:
* - Student registration with personal and academic information
* - Course management with credit hours and grade tracking
* - Automatic GPA calculation using weighted averages
* - Academic transcript generation and reporting
* - Search and display student records and statistics
* - Data persistence with file storage and retrieval
* - Input validation and error handling

# Concepts Demonstrated:
* - Structure arrays for data management
* - File I/O operations for data persistence
* - Mathematical calculations and algorithms
* - Menu-driven user interface
* - Data validation and error checking
* - Statistical analysis and reporting
* ========================================


* ========================================
# COMPILATION AND EXECUTION:
* ========================================

# To compile:
*   gcc -o grade_manager main.c

# To run:
*   ./grade_manager

* ========================================
# TESTING SUGGESTIONS:
* ========================================

# Student Management:
*   1. Add multiple students with different programs
*   2. View all registered students
*   3. Search for specific student records

# Grade Entry:
*   1. Add courses with different credit values
*   2. Enter grades for various subjects
*   3. Test with different grading scales (0-100)

# GPA Calculations:
*   1. Calculate GPA for single student
*   2. Verify GPA with manual calculations
*   3. Test edge cases (all A's, all F's, mixed grades)

# Data Persistence:
*   1. Save data after operations
*   2. Restart program and load previous data
*   3. Verify data integrity after reload

# Sample Test Cases:
*   Student: John Doe, Computer Science
*   Courses: 
*     - Programming (4 credits, 85%)
*     - Mathematics (3 credits, 92%)
*     - Physics (3 credits, 78%)
*   Expected GPA: ~3.2 (verify calculation)

*   Student: Jane Smith, Business
*   Courses:
*     - Economics (3 credits, 95%)
*     - Accounting (4 credits, 88%)
*     - Marketing (3 credits, 91%)
*   Expected GPA: ~3.8