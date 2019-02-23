#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void GetRecord(int & record) //Gets the record number of tries from the text file record.txt.
{
	string srecord;
	fstream file;
	file.open("record.txt");
	if (file.is_open())
	{
		getline(file, srecord);
		record = stoi(srecord);
		file.close();
	}
	else
	{
		cout << "Error. Text file \"record\" was not opened properly." << endl;
	}
}

void SetRecord(int & record) //Puts the new record number of tries into the text file record.txt.
{
	string srecord;
	fstream file;
	file.open("record.txt", ios::out | ios::trunc);
	if (file.is_open())
	{
		file << record;
		file.close();
	}
	else
	{
		cout << "Error. Text file \"record\" was not opened properly." << endl;
	}
}
