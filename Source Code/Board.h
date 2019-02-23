#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
bool CheckDuplicates(int, vector <int> &);

void FillBoard(int fullBoard[][4]) //Fills the board with randomly placed pair of 1-8 numbers.
{
	vector <int> duplicates; //Vector that saves used number positions.
	int numbers[16] = { 1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8 };
	int position;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			do
			{
				position = rand() % 16;
			} while (CheckDuplicates(position, duplicates));
			fullBoard[i][j] = numbers[position];
		}
	}
}

bool CheckDuplicates(int position, vector <int> & duplicates) //Checks if the randomly gotten position was already used.
{
	for (int i = 0; i < duplicates.size(); i++)
	{
		if (position == duplicates[i]) //Position was already used before, try again.
			return true;
	}
	duplicates.push_back(position); //New position is saved for next checks.
	return false;
}
