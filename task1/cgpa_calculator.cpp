/*
 * ============================================================
 *  CodeAlpha Internship - C++ Programming
 *  Task 1: CGPA Calculator
 *  ------------------------------------------------------------
 *  This program calculates the GPA for a semester and the
 *  overall CGPA based on course grades and credit hours.
 * ============================================================
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// ---------- Structure to hold course information ----------
struct Course {
    string name;
    char grade;
    double creditHours;
    double gradePoint;
};

// ---------- Function: Convert letter grade to grade point ----------
double gradeToPoint(char grade) {
    switch (toupper(grade)) {
        case 'A': return 4.00;
        case 'B': return 3.00;
        case 'C': return 2.00;
        case 'D': return 1.00;
        case 'F': return 0.00;
        default:  return -1.00;   // invalid grade
    }
}

// ---------- Function: Print a horizontal line ----------
void printLine(int width = 60, char ch = '-') {
    cout << string(width, ch) << "\n";
}

// ---------- Function: Print the header ----------
void printHeader() {
    printLine(60, '=');
    cout << setw(40) << "CodeAlpha CGPA CALCULATOR" << "\n";
    printLine(60, '=');
}

// ---------- Function: Get a valid grade from the user ----------
char getValidGrade(int courseNumber) {
    char grade;
    while (true) {
        cout << "  Enter grade for course " << courseNumber
             << " (A/B/C/D/F): ";
        cin >> grade;
        grade = toupper(grade);

        if (grade == 'A' || grade == 'B' || grade == 'C' ||
            grade == 'D' || grade == 'F') {
            return grade;
        }
        cout << "  [!] Invalid grade. Please enter A, B, C, D, or F.\n";
    }
}

// ---------- Function: Get a valid credit hour value ----------
double getValidCreditHours(int courseNumber) {
    double hours;
    while (true) {
        cout << "  Enter credit hours for course " << courseNumber
             << " (e.g., 3): ";
        cin >> hours;

        if (hours > 0 && hours <= 6) {
            return hours;
        }
        cout << "  [!] Credit hours must be between 1 and 6.\n";
    }
}

// ---------- Function: Display the result table ----------
void displayResults(const vector<Course>& courses,
                    double totalCredits,
                    double totalGradePoints) {

    cout << "\n";
    printLine(60, '=');
    cout << setw(35) << "RESULT SUMMARY" << "\n";
    printLine(60, '=');
    cout << left  << setw(20) << "Course"
         << setw(10) << "Grade"
         << setw(12) << "Credits"
         << setw(12) << "Points" << "\n";
    printLine(60);

    for (const auto& c : courses) {
        cout << left  << setw(20) << c.name
             << setw(10) << c.grade
             << setw(12) << fixed << setprecision(1) << c.creditHours
             << setw(12) << fixed << setprecision(2) << c.gradePoint * c.creditHours
             << "\n";
    }

    printLine(60);
    cout << left << setw(30) << "Total Credit Hours:"
         << right << setw(10) << fixed << setprecision(1) << totalCredits << "\n";
    cout << left << setw(30) << "Total Grade Points:"
         << right << setw(10) << fixed << setprecision(2) << totalGradePoints << "\n";
    printLine(60);
}

// ---------- Main Function ----------
int main() {
    printHeader();

    int numCourses;
    cout << "\n  How many courses did you take this semester? ";
    cin >> numCourses;

    // Input validation for number of courses
    while (numCourses <= 0 || numCourses > 20) {
        cout << "  [!] Please enter a number between 1 and 20: ";
        cin >> numCourses;
    }

    vector<Course> courses;
    double totalCredits = 0.0;
    double totalGradePoints = 0.0;

    cout << "\n";
    printLine(60);
    cout << "  ENTER COURSE DETAILS\n";
    printLine(60);

    // ---------- Input loop ----------
    for (int i = 1; i <= numCourses; i++) {
        Course c;
        cout << "\n  Course " << i << ":\n";

        cout << "  Enter course name: ";
        cin.ignore();
        getline(cin, c.name);

        c.grade = getValidGrade(i);
        c.creditHours = getValidCreditHours(i);
        c.gradePoint = gradeToPoint(c.grade);

        totalCredits += c.creditHours;
        totalGradePoints += c.gradePoint * c.creditHours;

        courses.push_back(c);
    }

    // ---------- Display results ----------
    displayResults(courses, totalCredits, totalGradePoints);

    // ---------- Calculate GPA / CGPA ----------
    double gpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0.0;

    cout << "\n";
    printLine(60, '=');
    cout << "  Semester GPA : " << fixed << setprecision(2) << gpa << " / 4.00\n";

    // ---------- Optional: Overall CGPA (previous semesters) ----------
    char choice;
    cout << "\n  Do you want to calculate your overall CGPA? (y/n): ";
    cin >> choice;

    if (toupper(choice) == 'Y') {
        double prevCredits, prevGradePoints;

        cout << "  Enter total credit hours from previous semesters: ";
        cin >> prevCredits;
        cout << "  Enter total grade points from previous semesters: ";
        cin >> prevGradePoints;

        double overallCredits = prevCredits + totalCredits;
        double overallPoints  = prevGradePoints + totalGradePoints;
        double cgpa = (overallCredits > 0) ? (overallPoints / overallCredits) : 0.0;

        cout << "\n";
        printLine(60, '=');
        cout << "  Overall CGPA : " << fixed << setprecision(2) << cgpa << " / 4.00\n";
        printLine(60, '=');
    }

    cout << "\n  Thank you for using the CodeAlpha CGPA Calculator!\n";
    printLine(60, '=');

    return 0;
}
