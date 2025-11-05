 * ========================================
 # ADVANCED SCIENTIFIC CALCULATOR
 * ========================================
 
 * Author: GADZIDE Komi Joël
 * Date: June 2025
 * Language: C++
 
 # Description:
 * An advanced scientific calculator that parses and evaluates
 * mathematical expressions with proper operator precedence,
 * parentheses support, and scientific functions.
 
 # Features:
 * - Basic operations: +, -, *, /, ^(power), %(modulo)
 * - Scientific functions: sin, cos, tan, log, ln, sqrt, abs
 * - Expression parsing with Shunting Yard algorithm
 * - Variable support (x = 5, y = x * 2)
 * - Calculation history
 * - Unit conversions
 * - Parentheses and operator precedence
 
 # Concepts Demonstrated:
 * - Stack data structure
 * - Infix to Postfix conversion (Shunting Yard)
 * - Expression evaluation
 * - String parsing and tokenization
 * - Map for variables storage
 * ========================================
 

 * ========================================
 # COMPILATION AND EXECUTION:
 * ========================================
 
 # To compile:
 *   g++ -std=c++11 calculator.cpp -o calculator
 
 # To run:
 *   ./calculator
 
 * ========================================
 # TESTING SUGGESTIONS:
 * ========================================
 
 # Basic operations:
 *   2 + 3 * 4
 *   (2 + 3) * 4
 *   10 / 3
 *   2 ^ 8
 
 # Functions:
 *   sqrt(16)
 *   sin(30)
 *   log(100)
 *   abs(-5)
 
 # Variables:
 *   x = 10
 *   y = x * 2
 *   result = sqrt(x^2 + y^2)
 
 # Complex:
 *   (sin(45) + cos(45)) * sqrt(2)
 *   log(100) + ln(e^2)
 