//----------------------------------------------------------------------------
// File:	SinkTheFleetleet.cpp
// 
// Function:
//      main()
//----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>
#include "fleet.h"
using namespace std;
extern const char* shipNames[7];

//---------------------------------------------------------------------------------
// Function:	main()
// Title:		Set ShipInfo
// Description:
//				Runs the Sink the Fleet Game
// Programmer:	Paul Bladek
// modified by: Donald Fitzhugh
// 
// Date:		12/9/2012
//
// Version:		0.5
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Input:		
//
// Output:		
//
// Calls:		initializePlayer()
//				allocMem()
//				safeChoice()
//				getGrid()
//				printGrid()
//				resetGrid()
//				setships()
//				header()
//				getCoord()
//				deleteMem()
//				endBox()
//
// Called By:	n/a
//
// Parameters:	void
// 
// Returns:		int -- EXIT_SUCCESS upon successful completion
//
// History Log: 
//				12/9/2012 PB completed v 0.5
//   
//---------------------------------------------------------------------------------
int main(void)
{
	// const short TOTALPIECES = 17;
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	// short Player1Hits = 0;
	// short Player2Hits = 0;
	char again = 'N';
	char gridSize = 'S';
	char fileName[FILENAME_MAX];
	char willReadFile = false;
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	Cell coord = {0, 0};
	string message;
	string filename;
	Ship shipHit = NOSHIP;
	Player game[NUMPLAYERS] ;	// the two players in an array
	// other stuff ...

	do
	{
		system("cls");
		cout << endl;
		header(cout);
		gridSize = safeChoice("Which size grid to you want to use", 'S', 'L');
		
		if( gridSize == 'L')
		{
			numRows = LARGEROWS;
			numCols = LARGECOLS;
		}
		else
		{
			numRows = SMALLROWS;
			numCols = SMALLCOLS;
		}
		initializePlayer(game);		
		initializePlayer(game + 1);
		// dynamically create the rows of the array
		allocMem(game,gridSize);

		// ... your code goes here

		for(whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			// enter grid files or let users enter ships
			willReadFile = safeChoice("Player " + to_string(whichPlayer+1) + ", Would you like to read starting grid from a file?", 'Y', 'N');
			if (willReadFile == 'Y'){
				cout << "Enter File Name: ";
				safeRead(cin, fileName, "invalid filename.");
				whichPlayer -= !getGrid(game, whichPlayer, gridSize, fileName);
			}
			else{
				setships(game, gridSize, whichPlayer);
			}
		}

		system("cls");
		header(cout);
		cout << "press <enter> to start the battle. . .\n";
		while (cin.get() != '\n');

		whichPlayer = 0;
		while(!gameOver)
		{
			system("cls");
			printGrid(cout, game[whichPlayer].m_gameGrid[1], gridSize);
			cout << "Player " << whichPlayer + 1 << ", Enter Coordinates for firing:\n";
			Cell coord = getCoord(cin, gridSize);
			if (game[!whichPlayer].m_gameGrid[0][coord.m_row][coord.m_col] != NOSHIP)// &&
				// game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] != MISSED &&
				// game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] != HIT)
			{
				if (game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] == HIT || game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] == MISSED){
					cout << "You've already fired at there. Enter a different coordinate.\n";
					continue; // skips this part of the loop but doesn't break out of it
				}
				
				game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = HIT;
				// if (whichPlayer == 0)
					// Player1Hits++;
				// else
					// Player2Hits++;
				--game[!whichPlayer].m_piecesLeft;

				cout << "Hit!";
				cout << "\nPrepare for another shot! Press <enter>";
			}
			else
			{
				game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col] = MISSED;
				cout << "You've Missed!\n Changing players. Press <enter>";
				whichPlayer = !whichPlayer;
			}

			while (cin.get() != '\n');

			if (game[0].m_piecesLeft == 0 || game[1].m_piecesLeft == 0){
				gameOver = !gameOver;
				endBox(!whichPlayer);
			}
		}

		again = safeChoice("Would you like to play again?", 'Y', 'N');
		deleteMem(game, gridSize);
	}
	while(again == 'Y');

	return EXIT_SUCCESS;
} 
