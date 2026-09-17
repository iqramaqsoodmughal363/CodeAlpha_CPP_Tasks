/*
 * ============================================================
 *  CodeAlpha Internship - C++ Programming
 *  Task 3: Sudoku Solver
 *  ------------------------------------------------------------
 *  This program solves a 9x9 Sudoku puzzle using the
 *  backtracking algorithm.
 * ============================================================
 */

#include <iostream>
#include <string>

using namespace std;

// ---------- Sudoku grid (0 = empty cell) ----------
int grid[9][9] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

// ---------- Function: Print a horizontal line ----------
void printLine(int width = 60, char ch = '-') {
    cout << string(width, ch) << "\n";
}

// ---------- Function: Print the Sudoku grid ----------
void printGrid() {
    printLine(31, '=');
    cout << "        SUDOKU GRID\n";
    printLine(31, '=');

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << grid[row][col] << " ";
            if (col == 2 || col == 5) cout << "| ";
        }
        cout << "\n";
        if (row == 2 || row == 5) {
            printLine(31, '-');
        }
    }
    printLine(31, '=');
}

// ---------- Function: Check if a number is safe to place ----------
bool isSafe(int row, int col, int num) {
    // Check row
    for (int x = 0; x < 9; x++) {
        if (grid[row][x] == num) return false;
    }

    // Check column
    for (int x = 0; x < 9; x++) {
        if (grid[x][col] == num) return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) return false;
        }
    }

    return true;
}

// ---------- Function: Solve the Sudoku using backtracking ----------
bool solveSudoku() {
    int row, col;
    bool foundEmpty = false;

    // Find an empty cell
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                foundEmpty = true;
                break;
            }
        }
        if (foundEmpty) break;
    }

    // If no empty cell found, puzzle is solved
    if (!foundEmpty) return true;

    // Try numbers 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(row, col, num)) {
            grid[row][col] = num;

            // Recursively solve the rest
            if (solveSudoku()) return true;

            // Backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

// ---------- Main Function ----------
int main() {
    printLine(60, '=');
    cout << "     CodeAlpha SUDOKU SOLVER\n";
    printLine(60, '=');
    cout << "\n  Original Puzzle:\n\n";

    printGrid();

    cout << "\n  Solving...\n";

    if (solveSudoku()) {
        cout << "\n  [OK] Puzzle Solved!\n\n";
        printGrid();
    } else {
        cout << "\n  [!] No solution exists for this puzzle.\n";
    }

    printLine(60, '=');
    cout << "  Thank you for using CodeAlpha Sudoku Solver!\n";
    printLine(60, '=');

    return 0;
}
