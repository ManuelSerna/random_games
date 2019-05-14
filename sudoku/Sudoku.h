//***********************************************
// Sudoku Class interface
//***********************************************
#include <iostream>

using namespace std;

// Define size of sudoku board
const int ROWS = 9;
const int COLS = 9;

/*
The sudoku game board is a 9 x 9 game board, seperated 
into 9 smaller squares each made of 3 x 3 squares.

In each of these smaller squares, any integer cannot be
in the same column or row as the same integer, nor in the
same small square.

          0   1   2   3   4   5   6   7   8
        +===+===+===+===+===+===+===+===+===+
     0  |           |           |           | 
        |           |           |           | s1: (0-2)x(0-2)
     1  |    s1     |    s2     |    s3     | s2: (0-2)x(3-5)
        |           |           |           | s3: (0-2)x(6-8)
     2  |           |           |           |
        +===+===+===+===+===+===+===+===+===+
     3  |           |           |           | 
        |           |           |           | s4: (3-5)x(0-2)
     4  |    s4     |    s5     |    s6     | s5: (3-5)x(3-5)
        |           |           |           | s6: (3-5)x(6-8)
     5  |           |           |           | 
        +===+===+===+===+===+===+===+===+===+
     6  |           |           |           | 
        |           |           |           | s7: (6-8)x(0-2)
     7  |    s7     |    s8     |    s9     | s8: (6-8)x(3-5)
        |           |           |           | s9: (6-8)x(6-8)
     8  |           |           |           | 
        +===+===+===+===+===+===+===+===+===+
*/

class Sudoku
{
public:
    Sudoku();
    ~Sudoku();

    // Setters and Getters
    void SetRowCoord(int);// set row and col
    void SetColCoord(int);
    void SetCellValue(int);
    int GetRowCoord();
    int GetColCoord();

    // Board/Display Operations
    void InitBoard();// initialize elements in array to 0
    void UpdateBoard();// update board with user input
    void PrintBoard();// print updated sudoku board

private:
    // Variable coords for the game board
    int row;
    int col;
    int cellValue;

    // Array to store integers of sudoku board
    int SudokuBoard[ROWS][COLS];

    // Check for errors in user input
    bool CheckErrors();
    bool CheckSquares(int, int);
};
