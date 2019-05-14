//=========================================================================================
// Connect 4 Game
// Manuel Serna-Aguilera
//=========================================================================================
#include <iostream>
using namespace std;

const int ROWS = 6;
const int COLS = 7;

//=========================================================================================
// FUNCTION PROTOTYPES
//=========================================================================================
char getUserInput();
void startMenu();
void assignPlayerMarker(char &, char &);
void connect4();
    bool gameLoop(char [ROWS][COLS], char, char);
        void printBoard(char [ROWS][COLS]);
        void dropMarker(char [ROWS][COLS], bool [ROWS],char, int);
        bool boardFull(char [ROWS][COLS], char, char);
		bool playerWins(char [ROWS][COLS], char);
//=========================================================================================
// FUNCTION DECLARATIONS
//=========================================================================================
//-----------------------------------------------------------------------------------------
// Get INPUT FROM USER - return a character
//-----------------------------------------------------------------------------------------
char getUserInput()
{
    char a = ' ';

    cout << "Your answer: ";
    cin >> a;// user inputs character

    // no error checking, return answer
    return a;
}
//-----------------------------------------------------------------------------------------
// Display Start Menu
//-----------------------------------------------------------------------------------------
void startMenu()
{
	cout << "\n======================================================\n";
    cout << "1. Play Game." << endl;
    cout << "2. Exit.";
	cout << "\n======================================================\n";

    // Get user input and either exit
    switch(getUserInput())
    {
        case '1':
            connect4();
            break;
        case '2':
            //leave program
            break;
        default:
            cout << "\nChoose a valid option.\n";
            startMenu();
            break;
    }
}
//-----------------------------------------------------------------------------------------
// ASSIGN PLAYER MARKERS TO P1 & P2
//-----------------------------------------------------------------------------------------
void assignPlayerMarker(char &p1, char &p2)
{
	cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Custom Markers.";
	cout << "\n++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "Type in a character marker for player 1:\n";
    p1 = getUserInput();

    // Enter do-while loop to make sure markers are different
    do
    {
        cout << "Type in a character marker for player 2:\n";
        p2 = getUserInput();
    }while(p1 == p2);
}
//-----------------------------------------------------------------------------------------
// CONNECT 4 GAME MENU
//-----------------------------------------------------------------------------------------
void connect4()
{
    // Declare variables for player markers for game board
    char p1 = '1';// board marker for player 1
    char p2 = '2';// board marker for player 2

    // Create array that will serve as connect 4 board
    char gameBoard[ROWS][COLS];// 6 x 7 table
    // Initialize array
    for(int r = 0; r < ROWS; r++)
    {
        for(int c = 0; c < COLS; c++)
        {
            gameBoard[r][c] = ' ';
        }
    }

    // Let players input characters for their markers
    assignPlayerMarker(p1, p2);

    // Enter game loop
    cout << "\nLET THE GAME BEGIN!\n";
    if(gameLoop(gameBoard, p1, p2))
	{
		cout << "Winner!\n";
	}
	else
	{
		cout << "No one wins!\n";
	}

    // Note: exiting this function marks the end of the game
}
//-----------------------------------------------------------------------------------------
// LOOP GAME UNTIL ONE PLAYER WINS
//-----------------------------------------------------------------------------------------
bool gameLoop(char gameBoard[ROWS][COLS], char p1, char p2)
{
    bool turn = 0;// dictate whose turn it is
	int col_choice = 0;// user inputs column of choice

	// Use bool arrays to check if a slot is already occupied, intialize all to false 0
	// KEY: col_N[0] bottom, col_N[5] top
	bool col1[ROWS] = {0,0,0,0,0,0};
	bool col2[ROWS] = {0,0,0,0,0,0};
	bool col3[ROWS] = {0,0,0,0,0,0};
	bool col4[ROWS] = {0,0,0,0,0,0};
	bool col5[ROWS] = {0,0,0,0,0,0};
	bool col6[ROWS] = {0,0,0,0,0,0};
	bool col7[ROWS] = {0,0,0,0,0,0};

    // Loop: Player 1 and 2 will alternate turns after dropping their
    // respective markers on the board. The maker is dropped and the
    // game board is updated. Then a function will check for a four
    // in a row, and will set the "continueGame" to false.

	printBoard(gameBoard);

    while(true)
    {		
        // Now prompt player 1 or 2 to drop their marker
		if(!turn)
		{
			// get user input on which column to drop marker into
            cout << "\nPlayer 1:\n";
            cout << "What column would you like to drop your \"" << p1 << "\" on?\n";
			cin >> col_choice;

			// Choose column
			switch(col_choice)
			{
				case 1:
					dropMarker(gameBoard, col1, p1, col_choice);
					break;
				case 2:
					dropMarker(gameBoard, col2, p1, col_choice);
					break;
				case 3:
					dropMarker(gameBoard, col3, p1, col_choice);
					break;
				case 4:
					dropMarker(gameBoard, col4, p1, col_choice);
					break;
				case 5:
					dropMarker(gameBoard, col5, p1, col_choice);
					break;
				case 6:
					dropMarker(gameBoard, col6, p1, col_choice);
					break;
				case 7:
					dropMarker(gameBoard, col7, p1, col_choice);
					break;
				default:
					cout << "Invalid input. Oh well.\n";
					col_choice = 0;// reinitialize
					break;
			}
			turn = 1;// now it's p1's turn
		}
		else
		{
			// get user input on which column to drop marker into
            cout << "\nPlayer 2:\n";
            cout << "What column would you like to drop your \"" << p2 << "\" on?\n";
			cin >> col_choice;// go down to correct index
			
			// Choose column
			switch(col_choice)
			{
				case 1:
					dropMarker(gameBoard, col1, p2, col_choice);
					break;
				case 2:
					dropMarker(gameBoard, col2, p2, col_choice);
					break;
				case 3:
					dropMarker(gameBoard, col3, p2, col_choice);
					break;
				case 4:
					dropMarker(gameBoard, col4, p2, col_choice);
					break;
				case 5:
					dropMarker(gameBoard, col5, p2, col_choice);
					break;
				case 6:
					dropMarker(gameBoard, col6, p2, col_choice);
					break;
				case 7:
					dropMarker(gameBoard, col7, p2, col_choice);
					break;
				default:
					cout << "Invalid input. Oh well.\n";
					col_choice = 0;// reinitialize
					break;
			}
            turn = 0;// now it's p2's turn
		}

		printBoard(gameBoard);// update board

		// Chcek if either player has won or if board is full
		if(boardFull(gameBoard, p1, p2))
		{
			return false;
		}		
		if(playerWins(gameBoard, p1) || playerWins(gameBoard, p2))
		{
			return true;
		}
		
    }
}
//-----------------------------------------------------------------------------------------
// PRINT GAME BOARD
//-----------------------------------------------------------------------------------------
void printBoard(char a[ROWS][COLS])
{
	cout << "\n--------------------------------------------\n\n";
    for(int x = 0; x < ROWS; x++)
    {
        cout << "\t|";
        for(int y = 0; y < COLS; y++)
        { cout << a[x][y] << "|"; }
        cout << endl;
    }
	cout << "\t===============\n";
	cout << "\t|1|2|3|4|5|6|7|\n";
	cout << "\n--------------------------------------------\n\n";
}
//-----------------------------------------------------------------------------------------
// PLAYER DROPS MARKER ONTO BOARD
//-----------------------------------------------------------------------------------------
void dropMarker(char gameBoard[ROWS][COLS], bool colN[ROWS],char p, int col)
{
	int row = ROWS-1;// determine row after for loop
	int actual_col = col-1;// offset index for column
	
	// Go down array, 
	// [0] bottom ... [5] top
	while((colN[row] != 0) && (row >= 0))
	{
		row--;// keep going until you see an empty slot in a column
	}

	if(row < 0)
	{
		return;
	}

	// Assign player marker if column has space on it
	colN[row] = true;// space is taken now
	gameBoard[row][actual_col] = p;
}
//-----------------------------------------------------------------------------------------
// BOARD FULL and if no one wins
//-----------------------------------------------------------------------------------------
bool boardFull(char gameBoard[ROWS][COLS], char p1, char p2)
{
	int count = 0;	

	for(int r = 0; r < ROWS; r++)
	{
		for(int c = 0; c < COLS; c++)
		{
			if((gameBoard[r][c] == p1) || (gameBoard[r][c] == p2))
			{
				count++;
			}
		}
	}
	
	return (count == (ROWS * COLS));
}
//-----------------------------------------------------------------------------------------
// PLAYER WINS
//-----------------------------------------------------------------------------------------
bool playerWins(char gameBoard[ROWS][COLS], char pN)
{
	int x = 0;// to check rows
	int y = 0;// to check columns
	int count = 0;// incremet when consecutive chars identified

	// Check verticals, go up columms
	for(int c = 0; c < COLS; c++)
	{
		// go up column (going up rows)
		for(int r = 0; r < ROWS; r++)
		{
			if(pN == gameBoard[r][c])
			{
				count++;// start cycle or maintain
			}
			else
			{
				count = 0;// broken cycle to get to 4
			}
			if(count == 4)
			{ return true; }
		}
	}

	// Check horizontals, go right across rows (crossing columns)
	for(int r = 0; r < ROWS; r++)
	{
		for(int c = 0; c < COLS; c++)
		{
			if(pN == gameBoard[r][c])
			{
				count++;// start cycle or maintain
			}
			else
			{
				count = 0;// broken cycle to get to 4
			}
			if(count == 4)
			{ return true; }
		}
	}
	
	// Check diagonals, reach four corners to find 4-in-a-row
	// Case: Upper Right (UR)
	for(int r = 0; r < ROWS; r++)
	{
		for(int c = 0; c < COLS; c++)
		{ 
			x = r;
			y = c;

			while((gameBoard[x][y] == pN) && (x >= 0) && (x < COLS) && (y >= 0) && (y < COLS))
			{
				count++;
				x--;
				y++;
				if(count == 4) { return true; }
			}
			count = 0;

			// Case: Lower Right (LR)
			x = r;
			y = c;

			while((gameBoard[x][y] == pN) && (x >= 0) && (x < COLS) && (y >= 0) && (y < COLS))
			{
				count++;
				x++;
				y++;
				if(count == 4) { return true; }
			}
			count = 0;

			// Case: Lower Right (LR)
			x = r;
			y = c;

			while((gameBoard[x][y] == pN) && (x >= 0) && (x < COLS) && (y >= 0) && (y < COLS))
			{
				count++;
				x++;
				y--;
				if(count == 4) { return true; }
			}
			count = 0;

			// Case: Lower Left (LL)
			x = r;
			y = c;

			while((gameBoard[x][y] == pN) && (x >= 0) && (x < COLS) && (y >= 0) && (y < COLS))
			{
				count++;
				x--;
				y--;
				if(count == 4) { return true; }
			}
			count = 0;
		}
	}

	return false;// the game goes on
}
//=========================================================================================
// MAIN method
//=========================================================================================
int main()
{
	cout << "\t\t***********\n";
    cout << "\t\t*CONNECT 4*";
    cout << "\n\t\t***********";

    startMenu();

    return 0;
}
