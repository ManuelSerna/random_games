//***********************************************
// Sudoku Game
//***********************************************
#include "Sudoku.h"
using namespace std;

int main()
{
    // Declarations
    Sudoku Game;
    int row = -1;// coords that user inputs
    int col = -1;
    int val = 0;// value to put on sudoku board
    Game.InitBoard();// set all cells to 0

    for(;;)
    {
        Game.SetRowCoord(row);
        Game.SetColCoord(col);

        Game.SetCellValue(val);
        Game.UpdateBoard();
        Game.PrintBoard();
    }

    return 0;
}
