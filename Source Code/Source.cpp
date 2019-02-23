#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Board.h"
#include "Record.h"

using namespace std;
void PrintInfo(int, int); //Prints number of tries and record.
void PrintBoard(int[][4]); //Board filled with zeroes and found pairs of numbers is printed.
void CheckInput(int &, int &, bool); //Takes the player's input and checks it.
void CheckChoice(int &, int &, int[][4], int[][4], bool); //Checks if the inputted coordinates have already been inputted.
void CheckPair(int, int, int, int, int[][4], int[][4], int &); //Checks if the selected numbers are a pair.  
bool CheckWon(int[][4], int, int); //Checks if the player has won and puts a new record if its reached.
bool Exit(); //Asks the player for a rematch.

int main()
{
	srand(time(NULL));
	do
	{
		bool turn = true;
		int x1, y1, x2, y2; //Coordinates for the space on the board.
		int tries = 0, record = 0;
		int fullBoard[4][4]; //The board that is filled with numbers.
		int emptyBoard[4][4] = { 0,0,0,0, //The board that is filled with zeroes in the beginning but gets filled with numbers as the player finds them.
			0,0,0,0,
			0,0,0,0,
			0,0,0,0 };
		FillBoard(fullBoard);
		GetRecord(record);
		system("cls");
		cout << "Welcome to the game of Memory!" << endl;
		cout << "The point of the game is to find 8 pair of numbers from 1-8 that are hidden amongst the zeroes. Good luck!" << endl;
		cout << "Press any key to continue.";
		_getch();
		do
		{
			system("cls");
			PrintInfo(tries, record);
			PrintBoard(emptyBoard);
			CheckInput(x1, y1, turn);
			CheckChoice(x1, y1, emptyBoard, fullBoard, turn);
			PrintBoard(emptyBoard);
			turn = false;
			CheckInput(x2, y2, turn);
			CheckChoice(x2, y2, emptyBoard, fullBoard, turn);
			PrintBoard(emptyBoard);
			turn = true;
			CheckPair(x1, y1, x2, y2, emptyBoard, fullBoard, tries);
		} while (CheckWon(emptyBoard, tries, record));
	} while (Exit());
}

void PrintInfo(int tries, int record)
{
	cout << "Choose two spaces on the board you want to check." << endl;
	cout << "Your number of tries: " << tries << "   " << "Record number of tries: " << record << endl;
}

void PrintBoard(int emptyBoard[4][4])
{
	cout << endl;
	cout << "    1 2 3 4" << endl << endl;
	for (int i = 0; i < 4; i++)
	{
		cout << " " << i + 1 << "  ";
		for (int j = 0; j < 4; j++)
		{
			cout << emptyBoard[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void CheckInput(int & x, int & y, bool turn)
{
	string place, input;
	if (turn)
		place = "first";
	else
		place = "second";
	cout << "Please input the number of the " << place << " row: ";
	getline(cin, input);
	while (input.size() > 1 || !(input[0] >= '1' && input[0] <= '4'))
	{
		cout << "Wrong input, please input a single number from 1 to 4: ";
		getline(cin, input);
	}
	x = stoi(input);
	x--; //User inputs a number 1-4 while the matrix is 0-3 x 0-3.

	cout << "Please input the number of the " << place << " column: ";
	getline(cin, input);
	while (input.size() > 1 || !(input[0] >= '1' && input[0] <= '4'))
	{
		cout << "Wrong input, please input a single number from 1 to 4: ";
		getline(cin, input);
	}
	y = stoi(input);
	y--;
}

void CheckChoice(int & x, int & y, int emptyBoard[][4], int fullBoard[][4], bool turn)
{
	if (emptyBoard[x][y] != 0)
	{
		cout << "You have inputted coordinates for an already uncovered field, please input different coordinates." << endl;
		CheckInput(x, y, turn);
		CheckChoice(x, y, emptyBoard, fullBoard, turn);
	}
	else
	{
		emptyBoard[x][y] = fullBoard[x][y]; //The coordinates are not used, change the emptyBoard.
	}
}

void CheckPair(int x1, int y1, int x2, int y2, int emptyBoard[][4], int fullBoard[][4], int & tries)
{
	if (fullBoard[x1][y1] != fullBoard[x2][y2])
	{
		cout << "You haven't found the same pair of numbers." << endl;
		emptyBoard[x1][y1] = 0; //The selected numbers aren't a pair so the emptyBoard gets reset.
		emptyBoard[x2][y2] = 0;
		tries++; //Only if the same pair of numbers haven't been found does the number of tries increase.
	}
	else
		cout << "You have found the same pair of numbers." << endl;
	cout << "Press any key to continue.";
	_getch();
}

bool CheckWon(int emptyBoard[4][4], int tries, int record)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (emptyBoard[i][j] == 0)
				return true;
		}
	}
	cout << endl;
	cout << "Congratulations! You have won the game!" << endl;
	if (tries < record)
	{
		cout << "Congratulations! You have set a new record!" << endl;
		cout << "New record: " << tries << "   " << "Previous record: " << record << endl;
		SetRecord(tries);
	}
	else if (tries == record)
	{
		cout << "Congratulations! Your number of tries is the same as the record number!" << endl;
	}
	else
	{
		cout << "Your number of tries: " << tries << "   " << "Record number of tries: " << record << endl;
	}
	return false;
}

bool Exit()
{
	string temp;
	cout << "Would you like to play again? Y/y za yes or any other key for no." << endl;
	getline(cin, temp);
	if (temp[0] == 'Y' || temp[0] == 'y')
		return true;
	else
		return false;
}


