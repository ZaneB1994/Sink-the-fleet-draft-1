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
// modified by:
// 
// Date:		12/9/2012
//
// Version:		0.5
// 
// Environment: Hardware: i3 
//              Software: OS: Windows 7; 
//              Compiles under Microsoft Visual C++ 2012
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
	short numRows = SMALLROWS;			// total number of rows in the array
	short numCols = SMALLCOLS;			// total number of columns in the array
	char again = 'N';
	char gridSize = 'S';
	char fileName[FILENAME_MAX];
	short whichPlayer = 0;
	bool gameOver = false;
	bool reshot = false;
	bool willReadFile = false;
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
			willReadFile = safeChoice("Player " + to_string(whichPlayer) + ", Would you like to read starting grid from a file?", 'Y', 'N');
			if (willReadFile){
				do{
					safeRead(cin, "Enter File Name: ", fileName);
				}while(getGrid(game, whichPlayer, gridSize, fileName));
			}
			else{

			}
		}
		whichPlayer = 0;
		while(!gameOver)
		{
		// ... a lot more stuff ...


			whichPlayer = !whichPlayer;  // switch players
		}

		again = safeChoice("Would you like to play again?", 'Y', 'N');
		deleteMem(game, gridSize);
	}
	while(again == 'Y');

	return EXIT_SUCCESS;
} 
