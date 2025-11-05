/*
 * ========================================
 * ADVANCED SCIENTIFIC CALCULATOR
 * ========================================
 *
 * Author: GADZIDE Komi Joël
 * Date: June 2025
 * Language: C++
 *
 * Description:
 * An advanced scientific calculator that parses and evaluates
 * mathematical expressions with proper operator precedence,
 * parentheses support, and scientific functions.
 *
 * Features:
 * - Basic operations: +, -, *, /, ^(power), %(modulo)
 * - Scientific functions: sin, cos, tan, log, ln, sqrt, abs
 * - Expression parsing with Shunting Yard algorithm
 * - Variable support (x = 5, y = x * 2)
 * - Calculation history
 * - Unit conversions
 * - Parentheses and operator precedence
 *
 * Concepts Demonstrated:
 * - Stack data structure
 * - Infix to Postfix conversion (Shunting Yard)
 * - Expression evaluation
 * - String parsing and tokenization
 * - Map for variables storage
 * ========================================
 */

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <algorithm>

using namespace std;

// ========================================
// TOKEN STRUCTURE
// Represents a single token in expression
// ========================================
enum TokenType {
    NUMBER,
    OPERATOR,
    FUNCTION,
    LPAREN,
    RPAREN,
    VARIABLE
};

struct Token {
    TokenType type;
    string value;
    double numValue;

    Token(TokenType t, string v, double n = 0.0)
        : type(t), value(v), numValue(n) {}
};

// ========================================
// CALCULATOR CLASS
// Main calculator with all operations
// ========================================
class ScientificCalculator {
private:
    map<string, double> variables;          // Store variables
    vector<string> history;                 // Calculation history
    map<string, int> operatorPrecedence;    // Operator priorities
    map<string, string> unitConversions;    // Unit conversion info

    // Initialize operator precedence
    void initializeOperators() {
        operatorPrecedence["+"] = 1;
        operatorPrecedence["-"] = 1;
        operatorPrecedence["*"] = 2;
        operatorPrecedence["/"] = 2;
        operatorPrecedence["%"] = 2;
        operatorPrecedence["^"] = 3;
    }

    // Check if character is operator
    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' ||
                c == '/' || c == '%' || c == '^');
    }

    // Check if string is a function
    bool isFunction(const string& str) {
        return (str == "sin" || str == "cos" || str == "tan" ||
                str == "log" || str == "ln" || str == "sqrt" ||
                str == "abs" || str == "exp");
    }

    // Get operator precedence
    int getPrecedence(const string& op) {
        if (operatorPrecedence.find(op) != operatorPrecedence.end()) {
            return operatorPrecedence[op];
        }
        return 0;
    }

    // Tokenize the input expression
    vector<Token> tokenize(const string& expression) {
        vector<Token> tokens;
        string current = "";

        for (size_t i = 0; i < expression.length(); i++) {
            char c = expression[i];

            // Skip whitespace
            if (isspace(c)) continue;

            // Numbers (including decimals)
            if (isdigit(c) || c == '.') {
                current += c;
                // Check if next char is also digit/decimal
                if (i + 1 < expression.length() &&
                    (isdigit(expression[i + 1]) || expression[i + 1] == '.')) {
                    continue;
                }
                tokens.push_back(Token(NUMBER, current, stod(current)));
                current = "";
            }
            // Letters (functions or variables)
            else if (isalpha(c)) {
                current += c;
                // Continue reading letters
                while (i + 1 < expression.length() && isalpha(expression[i + 1])) {
                    current += expression[++i];
                }

                if (isFunction(current)) {
                    tokens.push_back(Token(FUNCTION, current));
                } else {
                    tokens.push_back(Token(VARIABLE, current));
                }
                current = "";
            }
            // Operators
            else if (isOperator(c)) {
                string op(1, c);
                tokens.push_back(Token(OPERATOR, op));
            }
            // Parentheses
            else if (c == '(') {
                tokens.push_back(Token(LPAREN, "("));
            }
            else if (c == ')') {
                tokens.push_back(Token(RPAREN, ")"));
            }
        }

        return tokens;
    }

    // Convert infix to postfix using Shunting Yard algorithm
    queue<Token> infixToPostfix(const vector<Token>& tokens) {
        queue<Token> output;
        stack<Token> operators;

        for (const Token& token : tokens) {
            switch (token.type) {
                case NUMBER:
                    output.push(token);
                    break;

                case VARIABLE:
                    // Replace variable with its value
                    if (variables.find(token.value) != variables.end()) {
                        output.push(Token(NUMBER, token.value, variables[token.value]));
                    } else {
                        throw runtime_error("Undefined variable: " + token.value);
                    }
                    break;

                case FUNCTION:
                    operators.push(token);
                    break;

                case OPERATOR:
                    while (!operators.empty() &&
                           operators.top().type != LPAREN &&
                           ((operators.top().type == FUNCTION) ||
                            (operators.top().type == OPERATOR &&
                             getPrecedence(operators.top().value) >= getPrecedence(token.value)))) {
                        output.push(operators.top());
                        operators.pop();
                    }
                    operators.push(token);
                    break;

                case LPAREN:
                    operators.push(token);
                    break;

                case RPAREN:
                    while (!operators.empty() && operators.top().type != LPAREN) {
                        output.push(operators.top());
                        operators.pop();
                    }
                    if (operators.empty()) {
                        throw runtime_error("Mismatched parentheses!");
                    }
                    operators.pop(); // Remove left parenthesis

                    // If there's a function on top, pop it too
                    if (!operators.empty() && operators.top().type == FUNCTION) {
                        output.push(operators.top());
                        operators.pop();
                    }
                    break;
            }
        }

        // Pop remaining operators
        while (!operators.empty()) {
            if (operators.top().type == LPAREN || operators.top().type == RPAREN) {
                throw runtime_error("Mismatched parentheses!");
            }
            output.push(operators.top());
            operators.pop();
        }

        return output;
    }

    // Apply binary operation
    double applyBinaryOperator(double a, double b, const string& op) {
        if (op == "+") return a + b;
        if (op == "-") return a - b;
        if (op == "*") return a * b;
        if (op == "/") {
            if (b == 0) throw runtime_error("Division by zero!");
            return a / b;
        }
        if (op == "%") {
            if (b == 0) throw runtime_error("Modulo by zero!");
            return fmod(a, b);
        }
        if (op == "^") return pow(a, b);

        throw runtime_error("Unknown operator: " + op);
    }

    // Apply function
    double applyFunction(double value, const string& func) {
        if (func == "sin") return sin(value * M_PI / 180.0); // Degrees to radians
        if (func == "cos") return cos(value * M_PI / 180.0);
        if (func == "tan") return tan(value * M_PI / 180.0);
        if (func == "log") {
            if (value <= 0) throw runtime_error("log: value must be positive!");
            return log10(value);
        }
        if (func == "ln") {
            if (value <= 0) throw runtime_error("ln: value must be positive!");
            return log(value);
        }
        if (func == "sqrt") {
            if (value < 0) throw runtime_error("sqrt: value must be non-negative!");
            return sqrt(value);
        }
        if (func == "abs") return fabs(value);
        if (func == "exp") return exp(value);

        throw runtime_error("Unknown function: " + func);
    }

    // Evaluate postfix expression
    double evaluatePostfix(queue<Token> postfix) {
        stack<double> values;

        while (!postfix.empty()) {
            Token token = postfix.front();
            postfix.pop();

            switch (token.type) {
                case NUMBER:
                    values.push(token.numValue);
                    break;

                case OPERATOR: {
                    if (values.size() < 2) {
                        throw runtime_error("Invalid expression!");
                    }
                    double b = values.top(); values.pop();
                    double a = values.top(); values.pop();
                    double result = applyBinaryOperator(a, b, token.value);
                    values.push(result);
                    break;
                }

                case FUNCTION: {
                    if (values.empty()) {
                        throw runtime_error("Invalid expression!");
                    }
                    double value = values.top(); values.pop();
                    double result = applyFunction(value, token.value);
                    values.push(result);
                    break;
                }

                default:
                    throw runtime_error("Unexpected token in postfix!");
            }
        }

        if (values.size() != 1) {
            throw runtime_error("Invalid expression!");
        }

        return values.top();
    }

public:
    // Constructor
    ScientificCalculator() {
        initializeOperators();
        // Initialize some common constants
        variables["pi"] = M_PI;
        variables["e"] = M_E;
    }

    // Main calculation function
    double calculate(const string& expression) {
        try {
            // Check if it's a variable assignment
            size_t equalPos = expression.find('=');
            if (equalPos != string::npos) {
                string varName = expression.substr(0, equalPos);
                string varExpr = expression.substr(equalPos + 1);

                // Remove whitespace from variable name
                varName.erase(remove_if(varName.begin(), varName.end(), ::isspace), varName.end());

                // Calculate the value
                double value = calculate(varExpr);
                variables[varName] = value;

                cout << varName << " = " << value << endl;
                return value;
            }

            // Tokenize
            vector<Token> tokens = tokenize(expression);

            // Convert to postfix
            queue<Token> postfix = infixToPostfix(tokens);

            // Evaluate
            double result = evaluatePostfix(postfix);

            // Add to history
            stringstream ss;
            ss << expression << " = " << fixed << setprecision(6) << result;
            history.push_back(ss.str());

            return result;

        } catch (const exception& e) {
            throw runtime_error(string("Error: ") + e.what());
        }
    }

    // Display all variables
    void displayVariables() {
        cout << "\n========================================" << endl;
        cout << "STORED VARIABLES" << endl;
        cout << "========================================" << endl;

        if (variables.empty()) {
            cout << "No variables defined." << endl;
        } else {
            for (const auto& pair : variables) {
                cout << left << setw(10) << pair.first << " = "
                     << fixed << setprecision(6) << pair.second << endl;
            }
        }
        cout << "========================================\n" << endl;
    }

    // Display calculation history
    void displayHistory() {
        cout << "\n========================================" << endl;
        cout << "CALCULATION HISTORY" << endl;
        cout << "========================================" << endl;

        if (history.empty()) {
            cout << "No calculations yet." << endl;
        } else {
            for (size_t i = 0; i < history.size(); i++) {
                cout << i + 1 << ". " << history[i] << endl;
            }
        }
        cout << "========================================\n" << endl;
    }

    // Clear history
    void clearHistory() {
        history.clear();
        cout << "History cleared!" << endl;
    }

    // Clear variables (except constants)
    void clearVariables() {
        double pi_value = variables["pi"];
        double e_value = variables["e"];
        variables.clear();
        variables["pi"] = pi_value;
        variables["e"] = e_value;
        cout << "Variables cleared!" << endl;
    }

    // Unit conversion menu
    void unitConversion() {
        cout << "\n========================================" << endl;
        cout << "UNIT CONVERSION" << endl;
        cout << "========================================" << endl;
        cout << "1. Temperature (Celsius <-> Fahrenheit)" << endl;
        cout << "2. Length (Meters <-> Feet)" << endl;
        cout << "3. Weight (Kilograms <-> Pounds)" << endl;
        cout << "4. Back to main menu" << endl;
        cout << "========================================" << endl;

        int choice;
        double value, result;

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "1. Celsius to Fahrenheit\n2. Fahrenheit to Celsius" << endl;
                int tempChoice;
                cin >> tempChoice;
                cout << "Enter value: ";
                cin >> value;

                if (tempChoice == 1) {
                    result = (value * 9.0 / 5.0) + 32.0;
                    cout << value << "°C = " << result << "°F" << endl;
                } else {
                    result = (value - 32.0) * 5.0 / 9.0;
                    cout << value << "°F = " << result << "°C" << endl;
                }
                break;

            case 2:
                cout << "1. Meters to Feet\n2. Feet to Meters" << endl;
                int lengthChoice;
                cin >> lengthChoice;
                cout << "Enter value: ";
                cin >> value;

                if (lengthChoice == 1) {
                    result = value * 3.28084;
                    cout << value << "m = " << result << "ft" << endl;
                } else {
                    result = value / 3.28084;
                    cout << value << "ft = " << result << "m" << endl;
                }
                break;

            case 3:
                cout << "1. Kilograms to Pounds\n2. Pounds to Kilograms" << endl;
                int weightChoice;
                cin >> weightChoice;
                cout << "Enter value: ";
                cin >> value;

                if (weightChoice == 1) {
                    result = value * 2.20462;
                    cout << value << "kg = " << result << "lbs" << endl;
                } else {
                    result = value / 2.20462;
                    cout << value << "lbs = " << result << "kg" << endl;
                }
                break;

            case 4:
                return;

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    // Help display
    void displayHelp() {
        cout << "\n========================================" << endl;
        cout << "CALCULATOR HELP" << endl;
        cout << "========================================" << endl;
        cout << "\nOPERATORS:" << endl;
        cout << "  +    Addition" << endl;
        cout << "  -    Subtraction" << endl;
        cout << "  *    Multiplication" << endl;
        cout << "  /    Division" << endl;
        cout << "  %    Modulo" << endl;
        cout << "  ^    Power" << endl;

        cout << "\nFUNCTIONS:" << endl;
        cout << "  sin(x)   Sine (degrees)" << endl;
        cout << "  cos(x)   Cosine (degrees)" << endl;
        cout << "  tan(x)   Tangent (degrees)" << endl;
        cout << "  log(x)   Base-10 logarithm" << endl;
        cout << "  ln(x)    Natural logarithm" << endl;
        cout << "  sqrt(x)  Square root" << endl;
        cout << "  abs(x)   Absolute value" << endl;
        cout << "  exp(x)   e^x" << endl;

        cout << "\nCONSTANTS:" << endl;
        cout << "  pi       3.14159..." << endl;
        cout << "  e        2.71828..." << endl;

        cout << "\nVARIABLES:" << endl;
        cout << "  x = 5        Assign value to variable" << endl;
        cout << "  y = x * 2    Use variables in expressions" << endl;

        cout << "\nEXAMPLES:" << endl;
        cout << "  2 + 3 * 4" << endl;
        cout << "  (2 + 3) * 4" << endl;
        cout << "  sqrt(16) + log(100)" << endl;
        cout << "  sin(30) + cos(60)" << endl;
        cout << "  2 ^ 8" << endl;
        cout << "  x = 10" << endl;
        cout << "  y = x * pi" << endl;
        cout << "========================================\n" << endl;
    }
};

// ========================================
// MAIN FUNCTION
// Program entry point
// ========================================
int main() {
    ScientificCalculator calc;
    int choice;
    string expression;

    cout << "\n========================================" << endl;
    cout << "  ADVANCED SCIENTIFIC CALCULATOR" << endl;
    cout << "========================================\n" << endl;

    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1. Calculate Expression" << endl;
        cout << "2. View Variables" << endl;
        cout << "3. View History" << endl;
        cout << "4. Clear History" << endl;
        cout << "5. Clear Variables" << endl;
        cout << "6. Unit Conversion" << endl;
        cout << "7. Help" << endl;
        cout << "0. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                cout << "\nEnter expression (or 'back' to return): ";
                getline(cin, expression);

                if (expression == "back") break;

                try {
                    double result = calc.calculate(expression);
                    cout << "\nResult: " << fixed << setprecision(6) << result << endl;
                } catch (const exception& e) {
                    cout << e.what() << endl;
                }
                break;
            }

            case 2:
                calc.displayVariables();
                break;

            case 3:
                calc.displayHistory();
                break;

            case 4:
                calc.clearHistory();
                break;

            case 5:
                calc.clearVariables();
                break;

            case 6:
                calc.unitConversion();
                break;

            case 7:
                calc.displayHelp();
                break;

            case 0:
                cout << "\nThank you for using the calculator!" << endl;
                cout << "Goodbye!\n" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}

/*
 * ========================================
 * COMPILATION AND EXECUTION:
 * ========================================
 *
 * To compile:
 *   g++ -std=c++11 calculator.cpp -o calculator
 *
 * To run:
 *   ./calculator
 *
 * ========================================
 * TESTING SUGGESTIONS:
 * ========================================
 *
 * Basic operations:
 *   2 + 3 * 4
 *   (2 + 3) * 4
 *   10 / 3
 *   2 ^ 8
 *
 * Functions:
 *   sqrt(16)
 *   sin(30)
 *   log(100)
 *   abs(-5)
 *
 * Variables:
 *   x = 10
 *   y = x * 2
 *   result = sqrt(x^2 + y^2)
 *
 * Complex:
 *   (sin(45) + cos(45)) * sqrt(2)
 *   log(100) + ln(e^2)
 *
 * ========================================
 */
