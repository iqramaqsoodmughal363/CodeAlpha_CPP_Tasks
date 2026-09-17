/*
 * ============================================================
 *  CodeAlpha Internship - C++ Programming
 *  Task 2: Login and Registration System
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

void printLine(int width = 60, char ch = '-') {
    cout << string(width, ch) << "\n";
}

void printHeader() {
    printLine(60, '=');
    cout << "        CodeAlpha LOGIN & REGISTRATION SYSTEM\n";
    printLine(60, '=');
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

bool usernameExists(const string& username) {
    ifstream file("users.txt");
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            string storedUser = line.substr(0, pos);
            if (storedUser == username) {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

void registerUser() {
    string username, password, confirmPassword;

    cout << "\n";
    printLine(60);
    cout << "  REGISTRATION\n";
    printLine(60);

    // Clear input buffer
    cin.ignore(1000, '\n');

    cout << "  Enter username: ";
    getline(cin, username);
    username = trim(username);

    if (username.length() < 3) {
        cout << "  [!] Username must be at least 3 characters long.\n";
        return;
    }

    if (usernameExists(username)) {
        cout << "  [!] Username already exists. Please choose another.\n";
        return;
    }

    cout << "  Enter password: ";
    getline(cin, password);
    password = trim(password);

    if (password.length() < 4) {
        cout << "  [!] Password must be at least 4 characters long.\n";
        return;
    }

    cout << "  Confirm password: ";
    getline(cin, confirmPassword);
    confirmPassword = trim(confirmPassword);

    if (password != confirmPassword) {
        cout << "  [!] Passwords do not match. Registration failed.\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    if (!file.is_open()) {
        cout << "  [!] Error: Could not open file for writing.\n";
        return;
    }

    file << username << "|" << password << "\n";
    file.close();

    cout << "\n  [OK] Registration successful! You can now log in.\n";
}

bool loginUser() {
    string username, password;

    cout << "\n";
    printLine(60);
    cout << "  LOGIN\n";
    printLine(60);

    cin.ignore(1000, '\n');

    cout << "  Enter username: ";
    getline(cin, username);
    username = trim(username);

    cout << "  Enter password: ";
    getline(cin, password);
    password = trim(password);

    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "  [!] No users registered yet. Please register first.\n";
        return false;
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find('|');
        if (pos != string::npos) {
            string storedUser = line.substr(0, pos);
            string storedPass = line.substr(pos + 1);

            if (storedUser == username && storedPass == password) {
                file.close();
                cout << "\n  [OK] Login successful! Welcome, " << username << "!\n";
                return true;
            }
        }
    }

    file.close();
    cout << "\n  [!] Invalid username or password.\n";
    return false;
}

int main() {
    int choice;

    while (true) {
        printHeader();
        cout << "\n  1. Register\n";
        cout << "  2. Login\n";
        cout << "  3. Exit\n";
        printLine(60);
        cout << "  Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3:
                cout << "\n  Thank you for using CodeAlpha System!\n";
                printLine(60, '=');
                return 0;
            default:
                cout << "\n  [!] Invalid choice. Please enter 1, 2, or 3.\n";
        }

        cout << "\n  Press Enter to continue...";
        cin.ignore(1000, '\n');
        cin.get();
        system("cls");
    }

    return 0;
}
