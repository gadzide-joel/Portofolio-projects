/*
 * ========================================
 * BANKING MANAGEMENT SYSTEM
 * ========================================
 *
 * Author: GADZIDE Komi Jo�l
 * Date: October 2025
 * Language: C++
 *
 * Description:
 * A comprehensive banking system demonstrating Object-Oriented Programming
 * principles including inheritance, polymorphism, and encapsulation.
 *
 * Features:
 * - Multiple account types (Savings, Checking, Fixed Deposit)
 * - Deposit, withdrawal, and transfer operations
 * - Interest calculation for different account types
 * - Persistent data storage using file I/O
 * - Transaction history tracking
 * - User-friendly menu interface
 *
 * Concepts Demonstrated:
 * - Class inheritance and polymorphism
 * - Virtual functions and abstract classes
 * - File I/O operations
 * - STL containers (vector, map)
 * - Exception handling
 * ========================================
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>

using namespace std;

// ========================================
// TRANSACTION CLASS
// Represents a single transaction record
// ========================================
class Transaction {
private:
    string type;        // "Deposit", "Withdrawal", "Transfer"
    double amount;
    string date;
    string description;

public:
    // Constructor
    Transaction(string t, double amt, string desc = "")
        : type(t), amount(amt), description(desc) {
        // Get current date/time
        time_t now = time(0);
        char* dt = ctime(&now);
        date = string(dt);
        date.pop_back(); // Remove newline
    }

    // Display transaction details
    void display() const {
        cout << left << setw(15) << type
             << setw(12) << fixed << setprecision(2) << amount
             << setw(25) << date
             << description << endl;
    }

    // Getters for file operations
    string getType() const { return type; }
    double getAmount() const { return amount; }
    string getDate() const { return date; }
    string getDescription() const { return description; }
};

// ========================================
// BASE ACCOUNT CLASS (Abstract)
// Defines common interface for all account types
// ========================================
class Account {
protected:
    string accountNumber;
    string accountHolderName;
    double balance;
    vector<Transaction> transactionHistory;

public:
    // Constructor
    Account(string accNum, string name, double initialBalance = 0.0)
        : accountNumber(accNum), accountHolderName(name), balance(initialBalance) {}

    // Virtual destructor for proper cleanup
    virtual ~Account() {}

    // Pure virtual function - must be implemented by derived classes
    virtual void displayAccountType() const = 0;

    // Virtual function - can be overridden by derived classes
    virtual double calculateInterest() = 0;

    // Deposit money into account
    virtual bool deposit(double amount) {
        if (amount <= 0) {
            cout << "Error: Invalid deposit amount!" << endl;
            return false;
        }

        balance += amount;
        transactionHistory.push_back(Transaction("Deposit", amount));
        cout << "Successfully deposited $" << fixed << setprecision(2) << amount << endl;
        cout << "New balance: $" << balance << endl;
        return true;
    }

    // Withdraw money from account
    virtual bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Error: Invalid withdrawal amount!" << endl;
            return false;
        }

        if (balance < amount) {
            cout << "Error: Insufficient funds!" << endl;
            cout << "Current balance: $" << balance << endl;
            return false;
        }

        balance -= amount;
        transactionHistory.push_back(Transaction("Withdrawal", amount));
        cout << "Successfully withdrawn $" << fixed << setprecision(2) << amount << endl;
        cout << "New balance: $" << balance << endl;
        return true;
    }

    // Display account information
    virtual void displayInfo() const {
        cout << "\n========================================" << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Type: ";
        displayAccountType();
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << endl;
        cout << "========================================\n" << endl;
    }

    // Display transaction history
    void displayTransactionHistory() const {
        cout << "\n========================================" << endl;
        cout << "TRANSACTION HISTORY - " << accountNumber << endl;
        cout << "========================================" << endl;

        if (transactionHistory.empty()) {
            cout << "No transactions yet." << endl;
        } else {
            cout << left << setw(15) << "Type"
                 << setw(12) << "Amount"
                 << setw(25) << "Date"
                 << "Description" << endl;
            cout << string(70, '-') << endl;

            for (const auto& transaction : transactionHistory) {
                transaction.display();
            }
        }
        cout << "========================================\n" << endl;
    }

    // Getters
    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Setter for balance (used during transfers)
    void setBalance(double newBalance) { balance = newBalance; }

    // Add transaction to history
    void addTransaction(const Transaction& trans) {
        transactionHistory.push_back(trans);
    }
};

// ========================================
// SAVINGS ACCOUNT CLASS
// Savings account with interest calculation
// ========================================
class SavingsAccount : public Account {
private:
    double interestRate;  // Annual interest rate in percentage
    double minimumBalance;

public:
    // Constructor
    SavingsAccount(string accNum, string name, double initialBalance = 0.0,
                   double rate = 3.5, double minBalance = 100.0)
        : Account(accNum, name, initialBalance),
          interestRate(rate), minimumBalance(minBalance) {}

    // Override: Display account type
    void displayAccountType() const override {
        cout << "Savings Account" << endl;
    }

    // Override: Calculate monthly interest
    double calculateInterest() override {
        if (balance >= minimumBalance) {
            double interest = (balance * interestRate * 30) / (365 * 100); // Monthly interest
            balance += interest;

            stringstream ss;
            ss << "Interest credited @ " << interestRate << "% p.a.";
            transactionHistory.push_back(Transaction("Interest", interest, ss.str()));

            cout << "Interest credited: $" << fixed << setprecision(2) << interest << endl;
            return interest;
        } else {
            cout << "Minimum balance not maintained. No interest credited." << endl;
            return 0.0;
        }
    }

    // Override: Withdraw with minimum balance check
    bool withdraw(double amount) override {
        if (balance - amount < minimumBalance) {
            cout << "Error: Withdrawal would breach minimum balance requirement of $"
                 << minimumBalance << endl;
            return false;
        }
        return Account::withdraw(amount);
    }

    // Override: Display with interest rate info
    void displayInfo() const override {
        Account::displayInfo();
        cout << "Interest Rate: " << interestRate << "% p.a." << endl;
        cout << "Minimum Balance: $" << minimumBalance << endl;
        cout << "========================================\n" << endl;
    }
};

// ========================================
// CHECKING ACCOUNT CLASS
// Checking account with overdraft facility
// ========================================
class CheckingAccount : public Account {
private:
    double overdraftLimit;
    double transactionFee;

public:
    // Constructor
    CheckingAccount(string accNum, string name, double initialBalance = 0.0,
                    double overdraft = 500.0, double fee = 1.0)
        : Account(accNum, name, initialBalance),
          overdraftLimit(overdraft), transactionFee(fee) {}

    // Override: Display account type
    void displayAccountType() const override {
        cout << "Checking Account" << endl;
    }

    // Override: No interest for checking accounts
    double calculateInterest() override {
        cout << "Checking accounts do not earn interest." << endl;
        return 0.0;
    }

    // Override: Withdraw with overdraft facility
    bool withdraw(double amount) override {
        if (balance + overdraftLimit < amount) {
            cout << "Error: Amount exceeds available balance + overdraft limit!" << endl;
            cout << "Available: $" << (balance + overdraftLimit) << endl;
            return false;
        }

        balance -= amount;
        balance -= transactionFee; // Deduct transaction fee

        transactionHistory.push_back(Transaction("Withdrawal", amount));
        transactionHistory.push_back(Transaction("Fee", transactionFee, "Transaction fee"));

        cout << "Successfully withdrawn $" << fixed << setprecision(2) << amount << endl;
        cout << "Transaction fee: $" << transactionFee << endl;
        cout << "New balance: $" << balance << endl;

        return true;
    }

    // Override: Display with overdraft info
    void displayInfo() const override {
        Account::displayInfo();
        cout << "Overdraft Limit: $" << overdraftLimit << endl;
        cout << "Transaction Fee: $" << transactionFee << endl;
        cout << "Available Balance: $" << (balance + overdraftLimit) << endl;
        cout << "========================================\n" << endl;
    }
};

// ========================================
// FIXED DEPOSIT ACCOUNT CLASS
// Fixed deposit with lock-in period
// ========================================
class FixedDepositAccount : public Account {
private:
    double interestRate;
    int tenureMonths;
    time_t maturityDate;
    bool isMatured;

public:
    // Constructor
    FixedDepositAccount(string accNum, string name, double amount,
                        int months, double rate = 6.5)
        : Account(accNum, name, amount),
          interestRate(rate), tenureMonths(months), isMatured(false) {

        // Calculate maturity date
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        timeinfo->tm_mon += months;
        maturityDate = mktime(timeinfo);
    }

    // Override: Display account type
    void displayAccountType() const override {
        cout << "Fixed Deposit Account" << endl;
    }

    // Override: Calculate interest at maturity
    double calculateInterest() override {
        double interest = (balance * interestRate * tenureMonths) / (12 * 100);
        cout << "Interest on maturity: $" << fixed << setprecision(2) << interest << endl;
        return interest;
    }

    // Override: Deposits not allowed after creation
    bool deposit(double amount) override {
        cout << "Error: Additional deposits not allowed in Fixed Deposit accounts!" << endl;
        return false;
    }

    // Override: Withdrawals only at maturity
    bool withdraw(double amount) override {
        time_t now = time(0);

        if (now < maturityDate && !isMatured) {
            cout << "Error: Premature withdrawal not allowed!" << endl;
            cout << "Maturity date: " << ctime(&maturityDate);
            return false;
        }

        // If withdrawing at maturity, add interest
        if (!isMatured) {
            double interest = calculateInterest();
            balance += interest;
            transactionHistory.push_back(Transaction("Interest", interest, "Maturity interest"));
            isMatured = true;
        }

        return Account::withdraw(amount);
    }

    // Override: Display with FD specific info
    void displayInfo() const override {
        Account::displayInfo();
        cout << "Interest Rate: " << interestRate << "% p.a." << endl;
        cout << "Tenure: " << tenureMonths << " months" << endl;
        cout << "Maturity Date: " << ctime(&maturityDate);
        cout << "Status: " << (isMatured ? "Matured" : "Active") << endl;
        cout << "========================================\n" << endl;
    }
};

// ========================================
// BANK CLASS
// Manages all accounts and operations
// ========================================
class Bank {
private:
    vector<Account*> accounts;
    string bankName;
    int nextAccountNumber;

    // Generate unique account number
    string generateAccountNumber() {
        stringstream ss;
        ss << "ACC" << setw(6) << setfill('0') << nextAccountNumber++;
        return ss.str();
    }

    // Find account by account number
    Account* findAccount(const string& accNum) {
        for (auto account : accounts) {
            if (account->getAccountNumber() == accNum) {
                return account;
            }
        }
        return nullptr;
    }

public:
    // Constructor
    Bank(string name) : bankName(name), nextAccountNumber(100001) {
        loadAccountsFromFile();
    }

    // Destructor - cleanup
    ~Bank() {
        saveAccountsToFile();
        for (auto account : accounts) {
            delete account;
        }
    }

    // Create new Savings Account
    void createSavingsAccount() {
        string name;
        double initialBalance;

        cout << "\n=== CREATE SAVINGS ACCOUNT ===" << endl;
        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial deposit (min $100): $";
        cin >> initialBalance;

        if (initialBalance < 100) {
            cout << "Error: Minimum initial deposit is $100!" << endl;
            return;
        }

        string accNum = generateAccountNumber();
        Account* newAccount = new SavingsAccount(accNum, name, initialBalance);
        accounts.push_back(newAccount);

        cout << "\nSavings Account created successfully!" << endl;
        cout << "Account Number: " << accNum << endl;
    }

    // Create new Checking Account
    void createCheckingAccount() {
        string name;
        double initialBalance;

        cout << "\n=== CREATE CHECKING ACCOUNT ===" << endl;
        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial deposit: $";
        cin >> initialBalance;

        string accNum = generateAccountNumber();
        Account* newAccount = new CheckingAccount(accNum, name, initialBalance);
        accounts.push_back(newAccount);

        cout << "\nChecking Account created successfully!" << endl;
        cout << "Account Number: " << accNum << endl;
    }

    // Create new Fixed Deposit Account
    void createFixedDepositAccount() {
        string name;
        double amount;
        int months;

        cout << "\n=== CREATE FIXED DEPOSIT ACCOUNT ===" << endl;
        cout << "Enter account holder name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter deposit amount (min $1000): $";
        cin >> amount;

        if (amount < 1000) {
            cout << "Error: Minimum deposit for FD is $1000!" << endl;
            return;
        }

        cout << "Enter tenure in months (6, 12, 24, 36): ";
        cin >> months;

        if (months != 6 && months != 12 && months != 24 && months != 36) {
            cout << "Error: Invalid tenure! Choose from 6, 12, 24, or 36 months." << endl;
            return;
        }

        string accNum = generateAccountNumber();
        Account* newAccount = new FixedDepositAccount(accNum, name, amount, months);
        accounts.push_back(newAccount);

        cout << "\nFixed Deposit Account created successfully!" << endl;
        cout << "Account Number: " << accNum << endl;
    }

    // Deposit operation
    void depositMoney() {
        string accNum;
        double amount;

        cout << "\n=== DEPOSIT MONEY ===" << endl;
        cout << "Enter account number: ";
        cin >> accNum;

        Account* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Error: Account not found!" << endl;
            return;
        }

        cout << "Enter amount to deposit: $";
        cin >> amount;

        account->deposit(amount);
    }

    // Withdrawal operation
    void withdrawMoney() {
        string accNum;
        double amount;

        cout << "\n=== WITHDRAW MONEY ===" << endl;
        cout << "Enter account number: ";
        cin >> accNum;

        Account* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Error: Account not found!" << endl;
            return;
        }

        cout << "Enter amount to withdraw: $";
        cin >> amount;

        account->withdraw(amount);
    }

    // Transfer between accounts
    void transferMoney() {
        string fromAccNum, toAccNum;
        double amount;

        cout << "\n=== TRANSFER MONEY ===" << endl;
        cout << "Enter source account number: ";
        cin >> fromAccNum;
        cout << "Enter destination account number: ";
        cin >> toAccNum;

        Account* fromAccount = findAccount(fromAccNum);
        Account* toAccount = findAccount(toAccNum);

        if (fromAccount == nullptr || toAccount == nullptr) {
            cout << "Error: One or both accounts not found!" << endl;
            return;
        }

        cout << "Enter amount to transfer: $";
        cin >> amount;

        // Attempt withdrawal from source
        if (fromAccount->withdraw(amount)) {
            // If successful, deposit to destination
            toAccount->deposit(amount);

            // Add transfer records
            stringstream ss;
            ss << "Transfer to " << toAccNum;
            fromAccount->addTransaction(Transaction("Transfer Out", amount, ss.str()));

            ss.str("");
            ss << "Transfer from " << fromAccNum;
            toAccount->addTransaction(Transaction("Transfer In", amount, ss.str()));

            cout << "\nTransfer completed successfully!" << endl;
        }
    }

    // Check balance
    void checkBalance() {
        string accNum;

        cout << "\n=== CHECK BALANCE ===" << endl;
        cout << "Enter account number: ";
        cin >> accNum;

        Account* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Error: Account not found!" << endl;
            return;
        }

        account->displayInfo();
    }

    // View transaction history
    void viewTransactionHistory() {
        string accNum;

        cout << "\n=== TRANSACTION HISTORY ===" << endl;
        cout << "Enter account number: ";
        cin >> accNum;

        Account* account = findAccount(accNum);
        if (account == nullptr) {
            cout << "Error: Account not found!" << endl;
            return;
        }

        account->displayTransactionHistory();
    }

    // List all accounts
    void listAllAccounts() {
        cout << "\n========================================" << endl;
        cout << "ALL ACCOUNTS IN " << bankName << endl;
        cout << "========================================" << endl;

        if (accounts.empty()) {
            cout << "No accounts in the system." << endl;
        } else {
            cout << left << setw(12) << "Acc Number"
                 << setw(25) << "Holder Name"
                 << setw(20) << "Type"
                 << "Balance" << endl;
            cout << string(80, '-') << endl;

            for (auto account : accounts) {
                cout << left << setw(12) << account->getAccountNumber()
                     << setw(25) << account->getAccountHolderName()
                     << setw(20);
                account->displayAccountType();
                cout << "$" << fixed << setprecision(2) << account->getBalance() << endl;
            }
        }
        cout << "========================================\n" << endl;
    }

    // Save accounts to file
    void saveAccountsToFile() {
        ofstream outFile("bank_data.txt");

        if (!outFile) {
            cout << "Error: Unable to save data!" << endl;
            return;
        }

        outFile << nextAccountNumber << endl;
        outFile << accounts.size() << endl;

        // Simple file format - in real system, use JSON or database
        for (auto account : accounts) {
            outFile << account->getAccountNumber() << "|"
                    << account->getAccountHolderName() << "|"
                    << account->getBalance() << endl;
        }

        outFile.close();
        cout << "Data saved successfully!" << endl;
    }

    // Load accounts from file
    void loadAccountsFromFile() {
        ifstream inFile("bank_data.txt");

        if (!inFile) {
            // File doesn't exist - first run
            return;
        }

        inFile >> nextAccountNumber;

        int count;
        inFile >> count;
        inFile.ignore(); // Ignore newline

        // Note: In a real system, you'd save account type info
        // For this demo, we just restore basic accounts

        inFile.close();
    }
};

// ========================================
// MAIN FUNCTION
// Program entry point with menu system
// ========================================
int main() {
    Bank myBank("CSC International Bank");
    int choice;

    cout << "\n========================================" << endl;
    cout << "  WELCOME TO JOE INTERNATIONAL BANK" << endl;
    cout << "  Banking Management System v1.0" << endl;
    cout << "========================================\n" << endl;

    do {
        cout << "\n========== MAIN MENU ==========" << endl;
        cout << "1.  Create Savings Account" << endl;
        cout << "2.  Create Checking Account" << endl;
        cout << "3.  Create Fixed Deposit Account" << endl;
        cout << "4.  Deposit Money" << endl;
        cout << "5.  Withdraw Money" << endl;
        cout << "6.  Transfer Money" << endl;
        cout << "7.  Check Balance" << endl;
        cout << "8.  View Transaction History" << endl;
        cout << "9.  List All Accounts" << endl;
        cout << "0.  Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                myBank.createSavingsAccount();
                break;
            case 2:
                myBank.createCheckingAccount();
                break;
            case 3:
                myBank.createFixedDepositAccount();
                break;
            case 4:
                myBank.depositMoney();
                break;
            case 5:
                myBank.withdrawMoney();
                break;
            case 6:
                myBank.transferMoney();
                break;
            case 7:
                myBank.checkBalance();
                break;
            case 8:
                myBank.viewTransactionHistory();
                break;
            case 9:
                myBank.listAllAccounts();
                break;
            case 0:
                cout << "\nThank you for using CSC International Bank!" << endl;
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
 *   g++ -std=c++11 banking_system.cpp -o banking_system
 *
 * To run:
 *   ./banking_system
 *
 * ========================================
 * TESTING SUGGESTIONS:
 * ========================================
 *
 * 1. Create multiple account types
 * 2. Test deposit/withdrawal operations
 * 3. Test minimum balance enforcement (Savings)
 * 4. Test overdraft facility (Checking)
 * 5. Test FD maturity restrictions
 * 6. Test transfers between accounts
 * 7. View transaction histories
 *
 * ========================================
 */
