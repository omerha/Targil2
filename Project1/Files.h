#pragma once
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class Files {


public:
	Files(string fileName) {
		bool illegalFile = false;
		int numOfRows = 0;
		string tmpReadFile;
		ifstream inFile(fileName);
		if (inFile.fail())
		{
			illegalFile = true;
		}
		while (!inFile.eof() && !illegalFile)
		{
			if (getline(inFile, tmpReadFile))
			{
				if (!(tmpReadFile.empty()))
				{ }
				//	movesArr[numOfRows++] = tmpReadFile;
			}
			else
			{
				//setPlayerStatus(badMoves, errorFile, 0);
			}
		}
	}
};