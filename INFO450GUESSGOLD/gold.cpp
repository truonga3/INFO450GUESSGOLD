//guessTheGold game Written by Alexander Truong 
#include <iostream>
#include <iomanip>
#include <time.h>                                   //Professor I've scrutinized over this but I have no idea why not ALL the b and g's align with the x and y labels... 
using namespace std;								//I can assure you though that the bombs and the golds do work and that you get an extra guess when you find one 
const int BOARDSIZEY = 8;							//Print table isn't perfect! the coordinates do not match I have no idea why D,: I tested with taking out srand null 
const int BOARDSIZEX = 8;                           // (UPDATE) I found  reason why the index positions are flipped!! I don't know what concept of 2d arrays
													// I'm missing in order to to fix this problem...DARN IT!!! 
void printboardTable(char populate[BOARDSIZEY][BOARDSIZEX]); // (UPDATE) turns out I flipped my xs and ys-HAHA- *sigh had to retype because row = y col = x
void printGameSign();										 
int createGold(char boardtable[BOARDSIZEY][BOARDSIZEX]);      
int guessInput(char boardTable[BOARDSIZEY][BOARDSIZEX]);
int printNewBoard(char populate[BOARDSIZEY][BOARDSIZEX]);

int main()
{
	//initialize size of our gameboard array 8x8 
	char  boardTable[BOARDSIZEY][BOARDSIZEX];
	int rows, cols;
	char input;

	do //loops so they can play again
	{
		//here we fill our 2d array with question marks
		for (rows = 0; rows < BOARDSIZEY; rows++)
		{
			for (cols = 0; cols < BOARDSIZEX; cols++)
			{
				boardTable[rows][cols] = '?';
			}
		}
		//now that the board is filled-
		//we print each index array position to simulate a table
		printboardTable(boardTable); //follow the functions for how the board works 
		printGameSign();
		createGold(boardTable);
		guessInput(boardTable);
		printNewBoard(boardTable);
		
		cout << "Play again? Hit y or Y" << endl;
		cin >> input;
	} while (input == 'Y' || input == 'y');
	system("pause");
	return 0;
}

void printboardTable(char populate[BOARDSIZEY][BOARDSIZEX])
{
	int y, x;
	cout << "    Guess where the Gold is, ";
	cout << endl;
	cout << " Enter the x and y coordiantes! ";
	cout << endl;
	cout << endl;
	cout << "  ";
	for (x = 0; x < BOARDSIZEX; x++) //print top x = column axis labels
	{
		cout << setw(3) << x + 1;
	}
	cout << endl;
	cout << "  _________________________";
	cout << endl;
	//printing all 2d array indexes[][]
	for (y = 0; y < BOARDSIZEY; y++)
	{
		cout << y + 1 << "|";
		for (x = 0; x < BOARDSIZEX; x++)
		{
			cout << setw(3) << populate[x][y];
		}
		cout << endl;
	}
	cout << "  _________________________";
	cout << endl;
}

void printGameSign()
{
	cout << "  ************************" << endl;
	cout << "  *      Find Gold!      *" << endl;
	cout << "  *  You have 5 Guesses  *" << endl;
	cout << "  *   5 pieces of gold   *" << endl;
	cout << "  *    and one bomb!     *" << endl;
	cout << "  *      Good Luck!      *" << endl;
	cout << "  ************************" << endl;
}
//here we use srand to store the number of the index position that we want to store our gs and bs 
int createGold(char boardTable[BOARDSIZEY][BOARDSIZEX])
{
	int gRow0, gRow1, gRow2, gRow3, gRow4;
	int gCol0, gCol1, gCol2, gCol3, gCol4;
	srand(time(NULL));
	int bRow; 
	int bCol;

	//how do I fix the issue of the rand()s printing G and B on top of each other with "!=" ??? 
		gRow0 = rand() % BOARDSIZEY; //modulus is a great way to make sure our values stay within our 8x8 
		gCol0 = rand() % BOARDSIZEX;

		gRow1 = rand() % BOARDSIZEY;
		gCol1 = rand() % BOARDSIZEX;

		gRow2 = rand() % BOARDSIZEY;
		gCol2 = rand() % BOARDSIZEX;

		gRow3 = rand() % BOARDSIZEY;
		gCol3 = rand() % BOARDSIZEX;

		gRow4 = rand() % BOARDSIZEY;
		gCol4 = rand() % BOARDSIZEX;

		boardTable[gRow0][gCol0] = 'G'; // these all could of been looped, but the amount of time it took to figure out the basics!!! 
		boardTable[gRow1][gCol1] = 'G';
		boardTable[gRow2][gCol2] = 'G';
		boardTable[gRow3][gCol4] = 'G';
		boardTable[gRow4][gCol4] = 'G';
		
		bRow = rand() % BOARDSIZEX;
		bCol = rand() % BOARDSIZEY;

		boardTable[bRow][bCol] = 'B';

	return 0;
}

int guessInput(char boardTable[BOARDSIZEY][BOARDSIZEX])
{
	int xGuess;
	int yGuess;
	int counter = 5;
	int points = 0;

	do
	{
		cout << "Enter a X coordinate: " << endl;
		cin >> xGuess;
		cout << "Enter a Y coordinate: " << endl; 
		cin >> yGuess; 
	//I've decided here that if they put the wrong coordinates they lose a guess...MWA-HA-HA-HA-HA !!! 
		//unintentional, but I'm taking the happy path 
		if (xGuess > 8)
		{
			cout << "X value is too large input a value less than 9" << endl;
		}
		if (yGuess > 8)
		{
			cout << "Y value is too large input a value less than 9" << endl;
		}

		if (counter <= 5)
		{
			cout << "You have " << counter -1 << " guesses left!" << endl;
			cout << endl;
			counter--;
		}

		if (boardTable[xGuess][yGuess] == 'G')
		{
			cout << "YOU FOUND GOLD!" << endl;
			cout << "You gained an extra guess!" << endl;
			boardTable[xGuess][yGuess] = 'F';
			counter++;
			points += 1; //store points
			cout << endl;
		}

		if (boardTable[xGuess][yGuess] == 'B')
		{
			cout << "   -----Oh no!----" << endl; 
			cout << "	You found a Bomb!" << endl;
			cout << "	---GAME OVER---" << endl;
			boardTable[xGuess][yGuess] = 'X';
			cout << endl;
			break;
			
		}
		
	}

	while (counter > 0);
	
	cout << "You got " << points << " gold!"<< endl; //show points
	cout << endl;

	return 0;
}

int printNewBoard(char boardTable[BOARDSIZEY][BOARDSIZEX])
{
	int y, x;
	cout << "Here's your board:" << endl;
	cout << "  ";
	for (x = 0; x < BOARDSIZEX; x++)
	{
		cout << setw(3) << x + 1;
	}
	cout << endl;
	cout << "  _________________________";
	cout << endl;
	
	for (y = 0; y < BOARDSIZEY; y++)
	{
		cout << y + 1 << "|";
		for (x = 0; x < BOARDSIZEX; x++)
		{
			if (boardTable[x][y] == '?')
			{
				cout << ' ';
			}
			else
			{
				cout << setw(3) << boardTable[x][y];
			}

		}
		cout << endl;
	}
	cout << "  _________________________";
	cout << endl;

	return 0;
}

//Professor Kelo it turns out I didn't fix it. The board is still flawed :'] the positions are not correct and I don't know why 