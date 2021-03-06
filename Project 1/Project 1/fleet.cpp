//----------------------------------------------------------------------------
// File:	fleet.cpp
// 
// Functions: 
//	  setShipInfo()	
//	  allocMem() 
//	  deleteMem()
//	  printShip() 
//	  printGrid() 
//	  initializePlayer() 
//	  setships()	      
//	  saveGrid()
//	  getGrid()
//	  getCoord()
//	  validLocation() 
//	  header() 
//	  endBox() 
//----------------------------------------------------------------------------
#include "fleet.h"
//---------------------------------------------------------------------------------
// YOU ARE RESPONSIBLE FOR CORRECT HEADERS -- one for each function
// include the definitions for each of the non-template functions
//    declared in fleet.h 
//---------------------------------------------------------------------------------

const char* shipNames[SHIP_SIZE_ARRAYSIZE] = 
	{"No Ship", "Mine Sweeper", "Submarine", "Frigate",
		"Battleship", "Aircraft Carrier"};
const int TOTALPIECES = 17; // total pieces in all ships

//---------------------------------------------------------------------------------
// Function:	setShipInfo()
// Title:		Set ShipInfo
// Description:
//		Sets struct ShipInfo fields
// Programmer: Donald Fitzhugh
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:
//
// Parameters:	shipInfoPtr: ShipInfo *; pointer to the ShipInfo to be set
//				name: Ship;	enumerated name of type of ship; default: NOSHIP
//				orientation: Direction;	enumerated direction; default: HORIZONTAL
//				row: unsigned short; row-coordinate in grid; default: 0
//				col: unsigned short; column-coordinate in grid; default: 0
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void setShipInfo(ShipInfo * shipInfoPtr, Ship name, Direction orientation,
	unsigned short row, unsigned short col)
{
	shipInfoPtr->m_name = name;
	shipInfoPtr->m_orientation = orientation;
	shipInfoPtr->m_bowLocation.m_row = row;
	shipInfoPtr->m_bowLocation.m_col = col;
}  

//---------------------------------------------------------------------------------
// Function:	allocMem()
// Title:		Allocate Memory
// Description:
//		allocates memory for current grids
// Programmer:	Paul Bladek
// modified by:	Donald Fitzhugh
// 
// Date:	9/13/06
//
// Version:	1.01
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of 2 players in the game
//		size: char;	'	S' or 'L' (small or large)
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 1.0 
//		9/13/06  PB completed v 1.01
//
//---------------------------------------------------------------------------------
void allocMem(Player players[], char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	try
	{
		for(short i = 0; i < NUMPLAYERS; ++i)
		{
			players[i].m_gameGrid[0] = nullptr;
			players[i].m_gameGrid[0] = new Ship*[numberOfRows];
			players[i].m_gameGrid[1] = nullptr;
			players[i].m_gameGrid[1] = new Ship*[numberOfRows];
			for(short j = 0; j < numberOfRows; ++j)
			{
				players[i].m_gameGrid[0][j] = nullptr;
				players[i].m_gameGrid[0][j] = new Ship[numberOfCols];
				players[i].m_gameGrid[1][j] = nullptr;
				players[i].m_gameGrid[1][j] = new Ship[numberOfCols];

				for(short k = 0; k < numberOfCols; ++k)
				{
					players[i].m_gameGrid[0][j][k] = NOSHIP;
					players[i].m_gameGrid[1][j][k] = NOSHIP;
				} // end for k
			} // end for j
		} // end for i
	}
	catch(exception e)
	{
		deleteMem(players, size);
		cerr << "exception: " << e.what() << endl;
		cout << "shutting down" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		exit(EXIT_FAILURE);
	}
}

//---------------------------------------------------------------------------------
// Function:	deleteMem()
// Title:		Delete Memory
// Description:
//		Safely deletes memory for grids
// Programmer:Donald Fitzhugh
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[]; 	the array of the 2 Players
//		size: char;	'	S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//   
//---------------------------------------------------------------------------------
void deleteMem(Player players[], char size) 
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	// your code goes here ...
	// delete[] in reverse order of allocMem()
	// be sure to check if the memory was allocated (!nullptr) BEFORE deleting
	for (short i = 0; i < NUMPLAYERS; ++i)
	{
		for (short j = 0; j < numberOfRows; ++j)
		{
			if (!(players[i].m_gameGrid[0][j] == nullptr))
				delete[] players[i].m_gameGrid[0][j];
			
			if (!(players[i].m_gameGrid[1][j] == nullptr))
				delete[] players[i].m_gameGrid[1][j];

			if (!(players[i].m_gameGrid[0] == nullptr) && (players[i].m_gameGrid[0][j] == nullptr))
				delete[] players[i].m_gameGrid[0];
			
			if (!(players[i].m_gameGrid[1] == nullptr) && (players[i].m_gameGrid[1][j] == nullptr))
				delete[] players[i].m_gameGrid[1];
			
		}
	} 

}

//---------------------------------------------------------------------------------
// Function:	printShip()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer:	Paul Bladek, Donald Fitzhugh
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Output:		three characters representing one ship to sout
//
// Calls:
//
// Called By:	printGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//				thisShip: Ship;	the Ship to be printed in the grid format
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void printShip(ostream & sout, Ship thisShip)
{	
	sout << ' ' ;
	switch(thisShip)
	{
		case NOSHIP: sout << ' ';
			break;
		case MINESWEEPER: sout << 'M';
			break;
		case SUB: sout << 'S';
			break;
		case FRIGATE: sout << 'F';
			break;
		case BATTLESHIP: sout << 'B';
			break;
		case CARRIER: sout << 'C';
			break;
		case HIT: sout << 'H';
			break;
		case MISSED: sout << MISS;
			break;
		default: sout << 'X';
	}
	sout << VERT ;
}

//---------------------------------------------------------------------------------
// Function:	printGrid()
// Title:	Print Ship 
// Description:
//		Print grid element for the proper ship
// Programmer: Donald Fitzhugh
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Output:	a single grid to sout
//
// Calls:	printShip()
//
// Called By:	main()
//		setships()
//		saveGrid()
//
// Parameters:	sout: ostream&;	the stream to print to
//		grid: Ship**;	the 2-D array of Ships 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void printGrid(ostream& sout, Ship** grid, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	int sideNumbers = 0;
	char topLetters = 'A';

	sout << ' ';
	for(short j = 1; j <= numberOfCols; ++j)
		sout << setw(3) << j;
	sout  << endl;

	for (int i = 0; i < numberOfRows; ++i)
	{
		sout << topLetters++ << VERT;
		for (int j = 0; j < numberOfCols && i < numberOfRows; j++)
		{
			printShip(sout, grid[i][j]);
		}
		sout << endl;
		for (int j = 0; j <= numberOfCols; j++)
		{
			sout << HORIZ << CROSS << HORIZ;
		}
		sout << endl;
	}
	// use printShip for each element in the grid


} 

//---------------------------------------------------------------------------------
// Function:	initializePlayer()
// Title:	Initialize Player 
// Description:
//		sets initial values for m_ships and m_piecesLeft
// Programmer:	Paul Bladek, Donald Fitzhugh
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:	main()
//
// Parameters:	playerPtr: Player*;	a pointer to the current Player
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB completed v 1.0
//     
//---------------------------------------------------------------------------------
void initializePlayer(Player* playerPtr)
{
	for(short i = 0; i < SHIP_SIZE_ARRAYSIZE; i++)
		setShipInfo(playerPtr->m_ships + i, static_cast<Ship>(i));
	
	playerPtr->m_piecesLeft = TOTALPIECES; 
}

//---------------------------------------------------------------------------------
// Function:	setships()
// Title:	Set Ships 
// Description:
//		Allows user to put ships in grid
// Programmer:	Paul Bladek, Donald Fitzhugh
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Input:	location and orientation using getCoord from cin
//
// Output:	prompts to cout
//
// Calls:	printGrid()
//		safeChoice()
//		getCoord()
//		saveGrid()
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players 
//		size: char;		'S' or 'L'
//		whichPlayer: short;	the player number (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
void setships(Player players[], char size, short whichPlayer)
{
	char input = 'V';
	char ok = 'Y';
	char save = 'N';
	ostringstream outSStream;
	Cell location = {0, 0};
	for(short j = 1; j < SHIP_SIZE_ARRAYSIZE; j++)
	{
		system("cls");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		outSStream.str("");
		outSStream << "Player " << whichPlayer + 1 << " Enter "
			<< shipNames[j] << " orientation";
		input =  safeChoice(outSStream.str(), 'V', 'H');
		players[whichPlayer].m_ships[j].m_orientation
			= (input == 'V') ? VERTICAL : HORIZONTAL;
		cout << "Player " << whichPlayer + 1 << " Enter " << shipNames[j] <<
			" bow coordinates <row letter><col #>: ";
		players[whichPlayer].m_ships[j].m_bowLocation = getCoord(cin, size);

		// if ok
		if(!validLocation(players[whichPlayer], j, size))
		{
			cout << "invalid location. Press <enter>" ;
			cin.get();
			j--; // redo
			continue;
		}
		// your code goes here ...

		short rowAdd = (players[whichPlayer].m_ships[j].m_orientation == VERTICAL) ? 1 : 0;
		short colAdd = (players[whichPlayer].m_ships[j].m_orientation == HORIZONTAL) ? 1 : 0;

		Ship ship = players[whichPlayer].m_ships[j].m_name;

		short shipSizei = shipSize[ship];
		Cell bowLocation = players[whichPlayer].m_ships[j].m_bowLocation;

		for (short i = 0; i < shipSizei; i++){
			players[whichPlayer].m_gameGrid[0][bowLocation.m_row + i * rowAdd][bowLocation.m_col + i * colAdd] = ship;
			// players[(whichPlayer) ? 0 : 1].m_gameGrid[1][bowLocation.m_row + i * rowAdd][bowLocation.m_col + i * colAdd] = ship;
		}

	} // end for j

	system("cls");
	printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
	save = safeChoice("\nSave starting grid?", 'Y', 'N');
	if(save == 'Y')
		saveGrid(players, whichPlayer, size);
}

//---------------------------------------------------------------------------------
// Function:	saveGrid()
// Title:	Save Grid 
// Description:
//		Saves the ship grid to a file
// Programmer: Donald Fitzhugh
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Output:	grid to specified file
//
// Calls:	printGrid()
//
// Called By:	setships()
//
// Parameters:	player: sPlayer[];	the array of 2 players
//		whichPlayer: short; the player number (0 or 1) 
//		size: char;	'S' or 'L'
// 
// Returns:	void
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
void saveGrid(Player players[], short whichPlayer, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;	
	// your code goes here ...
	char filename[25] = "";

	cout << "Enter name of file to save to (.shp will be added): ";
	safeRead(cin, filename, "invalid file.");

	string filestring = "";
	filestring = filestring + filename + ".shp";

	ofstream outputFile;
	outputFile.open(filestring.c_str(), ios::out);

	outputFile << size << ' ';

	Player p = players[whichPlayer];

	for (int i = 1; i < SHIP_SIZE_ARRAYSIZE; i++)
	{
		outputFile << p.m_ships[i].m_name << ' ';

		outputFile << ((p.m_ships[i].m_orientation == HORIZONTAL) ? 'H' : 'V') << ' ';

		char row = 'A';

		row += p.m_ships[i].m_bowLocation.m_row;

		outputFile << row;

		outputFile << p.m_ships[i].m_bowLocation.m_col + 1 << ' ';
	}

	outputFile.close();
}

//---------------------------------------------------------------------------------
// Function:	getGrid()
// Title:	GetGrid 
// Description:
//		Reads grid from a file and properly sets the ships
// Programmer:	Paul Bladek, Donald Fitzhugh
// modified by:	
// 
// Date:	9/12/06
//
// Version:	0.5
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Input:	grid from specified file
//
// Output:	prompts to cout
//
// Calls:
//
// Called By:	main()
//
// Parameters:	players: Player[];	the array of 2 players
//		whichPlayer: short;	the player number  (0 or 1) 
//		size: char;		'S' or 'L'
//		string fileName:	the name of the file to be opened for reading
// 
// Returns: bool -- 	true if the file is opened and read;
//			false otherwise
//
// History Log: 
//		9/12/06 PB comleted v 0.5
//     
//---------------------------------------------------------------------------------
bool getGrid(Player players[], short whichPlayer, char size, string fileName)
{
	string line;
	ifstream ifs;
	Ship ship = NOSHIP;
	short shipCount[SHIP_SIZE_ARRAYSIZE] = {0};
	char cell = ' ';
	char fsize = 'S';
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;
	bool validFile = true;

	try
	{
		ifs.open(fileName.c_str(), ios::in);
		if(!ifs)
		{
			cout << "could not open file " << fileName << endl
				<< " press <enter> to continue" << endl;
			cin.ignore(BUFFER_SIZE, '\n');
			return false;
		}
	}
	catch(exception e)
	{
		cout << "could not open file " << fileName << endl
			<< " press <enter> to continue" << endl;
		cin.ignore(BUFFER_SIZE, '\n');
		return false;
	}	
	// your code goes here ...
	if (!(ifs >> fsize))
		validFile = false;
	if (fsize == size && validFile){
		short shipCount = 0;
		bool shipAlreadyAdded[SHIP_SIZE_ARRAYSIZE - 1] = { false, false, false, false, false };
		while (ifs.good()){
			if (!(ifs >> cell)){
				validFile = false; break;
			}
			if (++shipCount > SHIP_SIZE_ARRAYSIZE - 1){
				validFile = false; break;
			}
			Ship ship = static_cast<Ship>(atoi(&cell));
			if (ship < MINESWEEPER || ship > CARRIER || shipAlreadyAdded[ship - 1]){
				validFile = false; break;
			}
			shipAlreadyAdded[ship - 1] = true;
			short shipSizei = shipSize[ship];
			if (!(ifs >> cell)){
				validFile = false; break;
			}
			if (!(cell == 'V' || cell == 'H')){
				validFile = false; break;
			}
			Direction orientation = (cell == 'V') ? VERTICAL : HORIZONTAL;
			char coord[3];
			if (!(ifs >> coord)){
				validFile = false; break;
			}
			istringstream iss;
			iss.str(coord);
			
			Cell bowLocation;
			bowLocation.m_row = static_cast<short>(iss.get() - 'A');
			iss >> bowLocation.m_col;
			--bowLocation.m_col;
			iss.clear();

			setShipInfo(&players[whichPlayer].m_ships[ship], ship, orientation, bowLocation.m_row, bowLocation.m_col);
			if (!validLocation(players[whichPlayer], ship, fsize)){
				validFile = false; break;
			}
			// setShipInfo(&players[whichPlayer].m_ships[ship], ship, orientation, bowLocation.m_row, bowLocation.m_col);
			// char shipSymbol;
			short rowAdd = (orientation == VERTICAL) ? 1 : 0;
			short colAdd = (orientation == HORIZONTAL) ? 1 : 0;

			for (short i = 0; i < shipSizei; i++){
				players[whichPlayer].m_gameGrid[0][bowLocation.m_row + i * rowAdd][bowLocation.m_col + i * colAdd] = ship;
				// players[(whichPlayer) ? 0 : 1].m_gameGrid[1][bowLocation.m_row + i * rowAdd][bowLocation.m_col + i * colAdd] = ship;
			}
		}

		system("cls");
		printGrid(cout, players[whichPlayer].m_gameGrid[0], size);
		if (safeChoice("OK?", 'Y', 'N') == 'N'){
			validFile = false;
		}
	}
	else
		validFile = false;

	ifs.close();

	if (!validFile){
		clearGrid(players, whichPlayer, size);
	}

	return validFile;
}

//---------------------------------------------------------------------------------
// Function:	getCoord()
// Title:	Get Coordinates 
// Description:
//		Returns a cell with coordinates set by user
// Programmer:	Paul Bladek, Donald Fitzhugh
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Input:	cell coordinates (in the form "A13" from sin
//
// Output:	prompts to cout
//
// Calls:	none
//
// Called By:	main()
//		setships()
//
// Parameters:	sin: istream&;	the stream to read from
//		size: char;	'S' or 'L'
// 
// Returns:	Cell location -- a cell containing the input coordinates
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
Cell getCoord(istream& sin, char size)
{
	short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;
	char highChar = static_cast<char>(numberOfRows - 1) + 'A';
	char row  = 'A';
	short col = 0;
	Cell location = {0, 0};
	do
	{
		col = 0;
		cout << "Row must be a letter from A to " << highChar 
			<< " and column must be from 1 to "  << numberOfCols << ": ";
		while((row = toupper(sin.get())) < 'A' || row  > highChar)
		{
			sin.ignore(BUFFER_SIZE, '\n');
			cout << "Row must be a letter from A to " << highChar 
				<< " and column must be from 1 to "  << numberOfCols << ": ";
		}
		sin >> col;
		if(!sin)
			sin.clear();
		sin.ignore(BUFFER_SIZE, '\n');
	}
	while(col < 1 || col > numberOfCols);
	
	location.m_col = col - 1;
	location.m_row = static_cast<short>(row - 'A');
	return location;
}

//---------------------------------------------------------------------------------
// Function:	validLocation()
// Title:	Valid Location 
// Description:
//		Can the ship legitimately go there?
// Programmer: Donald Fitzhugh
// 
// Date:	12/20/05
//
// Version:	0.1
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Calls:
//
// Called By:
//
// Parameters:	player: const Player&;	a reference to the specific Player
//		shipNumber: short;	the number of the ship (1 - 5)
//					in the array player.m_ships[]
//		size: char;		'S' or 'L'
// 
// Returns: bool -- 	true if the ship would not go off the edge
//				or cross another ship;
//			false otherwise
//
// History Log:
//		12/20/05 PB completed v 0.1
//     
//---------------------------------------------------------------------------------
bool validLocation(const Player& player, short shipNumber, char size)
{
	short numberOfRows = (toupper(size)=='L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size)=='L') ? LARGECOLS : SMALLCOLS;
	// your code goes here ...

	short row = player.m_ships[shipNumber].m_bowLocation.m_row;
	short col = player.m_ships[shipNumber].m_bowLocation.m_col;

	if (col < 0)
		return false;
	if (row < 0)
		return false;

	Direction orientation = player.m_ships[shipNumber].m_orientation;

	short rowAdd = (orientation == VERTICAL) ? 1 : 0;
	short colAdd = (orientation == HORIZONTAL) ? 1 : 0;

	for (int i = 0; i < shipSize[shipNumber]; ++i){
		if (col + i * colAdd > numberOfCols)
			return false;
		if (row + i * rowAdd > numberOfRows)
			return false;
		if (player.m_gameGrid[0][row + (i * rowAdd)][col + (i * colAdd)] != NOSHIP)
			return false;
	}

	//if (player.m_gameGrid.m_ships[shipSize] == players[i].m_gameGrid[0][j][k] = NOSHIP ){
	//	printShip;
	//else (players[whichplayer].m_gamegrid.m_ships[shipSize] = false)
	//	cout << " " << players[whichPlayer], j, size;
	//if (players[(whichplayer)].m_gamegrid.m_ships[shipSize] = true){
	//	cout << " " << players[(whichPlayer) ? 0 : 1].m_gameGrid[1][bowLocation.m_row + i * rowAdd][bowLocation.m_col + i * colAdd]
	//else (players[whichplayer].m_gamegrid.m_ships[shipSize] = false)
	//	cout << " " << players[whichPlayer], j, size;
	//}

	// replace the return value
	return true;
}

//---------------------------------------------------------------------------------
// Function:	header()
// Title:	header 
// Description:
//		Prints opening graphic
// Programmer:	Paul Bladek, Donald Fitzhugh
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	sout: ostream&;	the stream to print to
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void header(ostream& sout)
{
	const string empty;
	const string sink("SINK THE FLEET!");
	// your name goes here!
	const string by("Edmonds Community College CS 132");
	boxTop(sout, BOXWIDTH);
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, sink , BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxLine(sout, by, BOXWIDTH, 'C');
	boxLine(sout, empty, BOXWIDTH);
	boxBottom(sout, BOXWIDTH);
}

//---------------------------------------------------------------------------------
// Function:	endBox()
// Title:	End Box 
// Description:
//		prints closinging graphic
// Programmer:	Paul Bladek, Donald Fitzhugh
// 
// Date:	9/12/06
//
// Version:	1.0
// 
// Environment: Intel Core i7 
//                Software:   MS Windows 10; 
//                Compiles under Microsoft Visual C++.Net 2013
//
// Output:	
//
// Calls:	boxTop()
//		boxLine()
//		boxBottom()
//
// Called By:	main()
//
// Parameters:	player: short; the number of the winner (0 or 1)
// 
// Returns:	void
//
// History Log: 
//		9/12/06 PB comleted v 1.0
//     
//---------------------------------------------------------------------------------
void endBox(short player)
{
	const string empty;
	ostringstream msg;
	msg << "Congratulations player " << player + 1 << "!";
	boxTop(cout, BOXWIDTH);
	boxLine(cout, empty, BOXWIDTH);
	boxLine(cout, msg.str() , BOXWIDTH, 'C');
	boxLine(cout, empty, BOXWIDTH);
	boxBottom(cout, BOXWIDTH);
}

void clearGrid(Player players[], short whichPlayer, char size)
{
	short numberOfRows = (toupper(size) == 'L') ? LARGEROWS : SMALLROWS;
	short numberOfCols = (toupper(size) == 'L') ? LARGECOLS : SMALLCOLS;

	for (short i = 0; i < numberOfRows; ++i){
		for (short j = 0; j < numberOfCols; ++j){
			players[whichPlayer].m_gameGrid[0][i][j] = NOSHIP;
		}
	}
}

