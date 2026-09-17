/*
 * ============================================================
 *  CodeAlpha Internship - C++ Programming
 *  Task 4: Banking System
 *  ------------------------------------------------------------
 *  This program implements a simple banking system using
 *  Object-Oriented Programming (OOP) concepts.
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ---------- Function: Print a horizontal line ----------
void printLine(int width = 60, char ch = '-') {
    cout << string(width, ch) << "\n";
}

// ============================================================
//  CLASS: Transaction
// ============================================================
class Transaction {
public:
    string type;        // Deposit, Withdrawal, Transfer
    double amount;
    double balanceAfter;
    string date;

    Transaction(string t, double a, double b, string d) {
        type = t;
        amount = a;
        balanceAfter = b;
        date = d;
    }

    void display() const {
        cout << left << setw(15) << type
             << setw(15) << fixed << setprecision(2) << amount
             << setw(15) << balanceAfter
             << setw(15) << date << "\n";
    }
};

// ============================================================
//  CLASS: Account
// ============================================================
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(int accNum, double initialBalance = 0.0) {
        accountNumber = accNum;
        balance = initialBalance;
        if (initialBalance > 0) {
            transactions.push_back(Transaction("Opening", initialBalance, balance, "Today"));
        }
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }

    // Deposit
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "  [!] Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount, balance, "Today"));
        cout << "  [OK] Deposited $" << fixed << setprecision(2) << amount
             << ". New balance: $" << balance << "\n";
    }

    // Withdraw
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "  [!] Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance) {
            cout << "  [!] Insufficient balance. Current balance: $"
                 << fixed << setprecision(2) << balance << "\n";
            return false;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount, balance, "Today"));
        cout << "  [OK] Withdrew $" << fixed << setprecision(2) << amount
             << ". New balance: $" << balance << "\n";
        return true;
    }

    // Receive transfer
    void receiveTransfer(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Received", amount, balance, "Today"));
    }

    // Display transaction history
    void showHistory() const {
        cout << "\n";
        printLine(60);
        cout << "  Transaction History - Account #" << accountNumber << "\n";
        printLine(60);
        cout << left << setw(15) << "Type"
             << setw(15) << "Amount"
             << setw(15) << "Balance"
             << setw(15) << "Date" << "\n";
        printLine(60);

        if (transactions.empty()) {
            cout << "  No transactions yet.\n";
        } else {
            for (size_t i = 0; i < transactions.size(); i++) {
                transactions[i].display();
            }
        }
        printLine(60);
    }

    // Display account info
    void showInfo() const {
        cout << "  Account #" << accountNumber
             << " | Balance: $" << fixed << setprecision(2) << balance << "\n";
    }
};

// ============================================================
//  CLASS: Customer
// ============================================================
class Customer {
private:
    int customerID;
    string name;
    Account* account;

public:
    Customer(int id, string n) {
        customerID = id;
        name = n;
        account = NULL;
    }

    ~Customer() {
        if (account != NULL) delete account;
    }

    int getID() const { return customerID; }
    string getName() const { return name; }
    Account* getAccount() const { return account; }

    void createAccount(int accNum, double initialBalance = 0.0) {
        if (account != NULL) {
            cout << "  [!] Customer already has an account.\n";
            return;
        }
        account = new Account(accNum, initialBalance);
        cout << "  [OK] Account #" << accNum << " created for "
             << name << ".\n";
    }

    void display() const {
        cout << "  Customer ID: " << customerID
             << " | Name: " << name << "\n";
        if (account != NULL) {
            account->showInfo();
        } else {
            cout << "  No account created yet.\n";
        }
    }
};

// ============================================================
//  MAIN FUNCTION
// ============================================================
int main() {
    vector<Customer> customers;
    int nextCustomerID = 1001;
    int nextAccountNumber = 5001;

    // Create a sample customer for testing
    Customer sample(nextCustomerID++, "Iqra Maqsood");
    sample.createAccount(nextAccountNumber++, 1000.0);
    customers.push_back(sample);

    int choice;

    while (true) {
        printLine(60, '=');
        cout << "        CodeAlpha BANKING SYSTEM\n";
        printLine(60, '=');
        cout << "  1. Create New Customer\n";
        cout << "  2. Create Account for Customer\n";
        cout << "  3. Deposit\n";
        cout << "  4. Withdraw\n";
        cout << "  5. Transfer Funds\n";
        cout << "  6. View Account Info\n";
        cout << "  7. View Transaction History\n";
        cout << "  8. View All Customers\n";
        cout << "  9. Exit\n";
        printLine(60);
        cout << "  Enter your choice (1-9): ";
        cin >> choice;

        // ---------- Create New Customer ----------
        if (choice == 1) {
            string name;
            cin.ignore(1000, '\n');
            cout << "  Enter customer name: ";
            getline(cin, name);

            Customer c(nextCustomerID++, name);
            customers.push_back(c);
            cout << "  [OK] Customer created. ID: "
                 << (nextCustomerID - 1) << "\n";
        }
        // ---------- Create Account ----------
        else if (choice == 2) {
            int custID;
            double initial;
            cout << "  Enter Customer ID: ";
            cin >> custID;

            bool found = false;
            for (size_t i = 0; i < customers.size(); i++) {
                if (customers[i].getID() == custID) {
                    cout << "  Enter initial deposit: $";
                    cin >> initial;
                    customers[i].createAccount(nextAccountNumber++, initial);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "  [!] Customer not found.\n";
        }
        // ---------- Deposit ----------
        else if (choice == 3) {
            int accNum;
            double amount;
            cout << "  Enter Account Number: ";
            cin >> accNum;
            cout << "  Enter Deposit Amount: $";
            cin >> amount;

            bool found = false;
            for (size_t i = 0; i < customers.size(); i++) {
                Account* a = customers[i].getAccount();
                if (a != NULL && a->getAccountNumber() == accNum) {
                    a->deposit(amount);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "  [!] Account not found.\n";
        }
        // ---------- Withdraw ----------
        else if (choice == 4) {
            int accNum;
            double amount;
            cout << "  Enter Account Number: ";
            cin >> accNum;
            cout << "  Enter Withdrawal Amount: $";
            cin >> amount;

            bool found = false;
            for (size_t i = 0; i < customers.size(); i++) {
                Account* a = customers[i].getAccount();
                if (a != NULL && a->getAccountNumber() == accNum) {
                    a->withdraw(amount);
                    found = true;
                    break;
                }
            }
            if (!found) cout << "  [!] Account not found.\n";
        }
        // ---------- Transfer ----------
        else if (choice == 5) {
            int fromAcc, toAcc;
            double amount;
            cout << "  Enter Sender Account Number: ";
            cin >> fromAcc;
            cout << "  Enter Receiver Account Number: ";
            cin >> toAcc;
            cout << "  Enter Transfer Amount: $";
            cin >> amount;

            Account* sender = NULL;
            Account* receiver = NULL;

            for (size_t i = 0; i < customers.size(); i++) {
                Account* a = customers[i].getAccount();
                if (a != NULL) {
                    if (a->getAccountNumber() == fromAcc) sender = a;
                    if (a->getAccountNumber() == toAcc)   receiver = a;
                }
            }

            if (sender == NULL || receiver == NULL) {
                cout << "  [!] Invalid sender or receiver account.\n";
            } else {
                if (sender->withdraw(amount)) {
                    receiver->receiveTransfer(amount);
                    cout << "  [OK] Transfer successful!\n";
                }
            }
        }
        // ---------- Account Info ----------
        else if (choice == 6) {
            int accNum;
            cout << "  Enter Account Number: ";
            cin >> accNum;

            bool found = false;
            for (size_t i = 0; i < customers.size(); i++) {
                Account* a = customers[i].getAccount();
                if (a != NULL && a->getAccountNumber() == accNum) {
                    a->showInfo();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "  [!] Account not found.\n";
        }
        // ---------- Transaction History ----------
        else if (choice == 7) {
            int accNum;
            cout << "  Enter Account Number: ";
            cin >> accNum;

            bool found = false;
            for (size_t i = 0; i < customers.size(); i++) {
                Account* a = customers[i].getAccount();
                if (a != NULL && a->getAccountNumber() == accNum) {
                    a->showHistory();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "  [!] Account not found.\n";
        }
        // ---------- View All Customers ----------
        else if (choice == 8) {
            cout << "\n";
            printLine(60, '=');
            cout << "        ALL CUSTOMERS\n";
            printLine(60, '=');
            for (size_t i = 0; i < customers.size(); i++) {
                customers[i].display();
                printLine(60);
            }
        }
        // ---------- Exit ----------
        else if (choice == 9) {
            cout << "\n  Thank you for using CodeAlpha Banking System!\n";
            printLine(60, '=');
            break;
        }
        else {
            cout << "  [!] Invalid choice. Please enter 1-9.\n";
        }

        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        cin.get();
        system("cls");
    }

    return 0;
}
