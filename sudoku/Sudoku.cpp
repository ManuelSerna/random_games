//***********************************************
// Sudoku interface Implementation
//***********************************************
#include "Sudoku.h"

using namespace std;

// Implementation of sudoku class
//==============================================================
// P: Constructor and destructor
// O: NA
//==============================================================
Sudoku::Sudoku()
{
    //cout << "\nconstructor\n";
}
//--------------------------------------------------------------
Sudoku::~Sudoku()
{
    //cout << "\ndestructor\n";
}
//==============================================================
// P: set user input for cell location and input value in 
//      specified cell
// O: NA
//==============================================================
void Sudoku::SetRowCoord(int num)
{
    cout << endl;
    do
    {
        cout << "Enter coordinate for row (0..8): ";
        cin >> num;
    }while((num < 0 ) || (num > 8));

    row = num;// resetting will occur when updating board
}
//--------------------------------------------------------------
void Sudoku::SetColCoord(int num)
{
    cout << endl;
    do
    {
        cout << "Enter coordinate for column (0..8): ";
        cin >> num;
    }while((num < 0 ) || (num > 8));

    col = num;// resetting will occur when updating board
}
//--------------------------------------------------------------
void Sudoku::SetCellValue(int num)
{
    cout << endl;
    do
    {
        cout << "Enter number (1..9): ";
        cin >> num;
    }while((num < 1 ) || (num > 9));
    cout << "--------------------------------------------------";

    cellValue = num;// resetting will occur when updating board
}
//==============================================================
// P: return values of coordinates previously input
// O: row or col
//==============================================================
int Sudoku::GetRowCoord()
{
    return row;
}
//--------------------------------------------------------------
int Sudoku::GetColCoord()
{
    return col;
}
//==============================================================
// P: initialize all game board elements to 0
// O: NA
//==============================================================
void Sudoku::InitBoard()
{
    for(int c = 0; c < ROWS; c++)
    {
        for(int r = 0; r < COLS; r++)
        {
            SudokuBoard[r][c] = 0;
        }
    }
}
//==============================================================
// P: update game board before printing it
// O: Error message if input is NOT valid
//==============================================================
void Sudoku::UpdateBoard()
{
    // PUT CONDITION HERE IF CheckError FUNCTION RETURNS TRUE
    // OTHERWISE DISPLAY MESSAGE TO USER
    if(CheckErrors())
    {
        SudokuBoard[row][col] = cellValue;
    }
    else
    {
        cout << "\nThat's invalid input! Please try another number.\n";
        cout << "--------------------------------------------------\n";
    }

    // Reset private members regardless if input is valid or not
    row = -1;
    col = -1;
}
//==============================================================
// P: print Sudoku game board after updating
// O: sudoku game board
//==============================================================
void Sudoku::PrintBoard()
{
    //cout << "\nprinting board\n";
    cout << "\n\n";
    cout << "   ";

    // Label columns
    for(int c = 0; c < COLS; c++)
        cout << "   " << c;

    // Create top border
    cout << endl << "    ";// 4 whitespaces
    for(int r = 0; r < ROWS; r++)
        cout << "+===";

    cout << "+\n";

    // Print the rest of the table
    for(int c = 0; c < ROWS; c++)
    {
        // print nth row
        cout << " " << c << "  | ";// label rows

        for(int r1 = 0; r1 < COLS; r1++)
        {
            cout << SudokuBoard[c][r1];// << " | ";// OR INCLUDE CONDITIONS HERE???
            if((r1 == 2) || (r1 == 5) || (r1 == 8))
                cout << " | ";// seperate 3x3 squares vertically
            else
                cout << " + ";
        }

        cout << endl << "    ";

        // print inter-row border
        for(int r2 = 0; r2 < ROWS; r2++)
        {
            if((c == 2) || (c == 5) || (c == 8))
                cout << "+===";// seperate 3x3 squares horizontally
            else
                cout << "+ + ";
        }
        cout << "+\n";
    }
}
//**************************************************************
// Private Members
//==============================================================
// P: perform operations based on user input (detailed below)
// O: true if - no other number matches input in square, and no
//      same numbers are in the same row and column (good to place in cell)
//    false if - any of the conditions above are violated
//    *Is called in "UpdateBoard" method
//==============================================================
bool Sudoku::CheckErrors()
{
    // Check for any same numbers in row
    for(int c = 0; c < COLS; c++)
    {
        if(SudokuBoard[row][c] == cellValue) return false;
    }
    // Check for any same numbers in column
    for(int r = 0; r < ROWS; r++)
    {
        if(SudokuBoard[r][col] == cellValue) return false;
    }

    // Check for any equal numbers in the same 3x3 square,
    // include ranges for the 3x3 squares so you won't get input errors
    // NOTE: RANGES HARDCODED WHEN CALLING "CheckSquares"

    if((row >= 0) && (row <= 2))
    {
        if((col >= 0) && (col <= 2)) { if(CheckSquares(0, 0)) return false; }
        if((col >= 3) && (col <= 5)) { if(CheckSquares(0, 3)) return false; }
        if((col >= 6) && (col <= 8)) { if(CheckSquares(0, 6)) return false; }
    }

    else if((row >= 3) && (row <= 5))
    {
        if((col >= 0) && (col <= 2)) { if(CheckSquares(3, 0)) return false; }
        if((col >= 3) && (col <= 5)) { if(CheckSquares(3, 3)) return false; }
        if((col >= 6) && (col <= 8)) { if(CheckSquares(3, 6)) return false; }
    }

    else if((row >= 6) && (row <= 8))
    {
        if((col >= 0) && (col <= 2)) { if(CheckSquares(6, 0)) return false; }
        if((col >= 3) && (col <= 5)) { if(CheckSquares(6, 3)) return false; }
        if((col >= 6) && (col <= 8)) { if(CheckSquares(6, 6)) return false; }
    }
    return true;// all conditions above are false
}
//==============================================================
// P: to check if integer input matches any integer in the 3x3
//  squares, check all squares in nested loops
// O: returns true if two numbers do match
//==============================================================
bool Sudoku::CheckSquares(int rowRange, int columnRange)
{
    for(int r = rowRange; r < (rowRange + 3); r++)
    {
        for(int c = columnRange; c < (columnRange + 3); c++)
        {
            if(SudokuBoard[r][c] == cellValue) { return true; }
        }
    }
    return false;// false = cells do NOT match, input is valid
}
