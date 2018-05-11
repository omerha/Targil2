#pragma once

#include <fstream>
#include <sstream>
#include "Player.h"
#define M 10 //colums
#define N 10 // rows
#define K 13 // The num of pieces of each player
#define MAX_MOVES 100
using namespace std;

class FilesPlayer : public Player {
	static int currentNumPlayer;
	bool illegalFile = false;
	int errLine = NULL;
//	Error error = noError;
//	Reason fileStatus = noReason;
	ifstream inFile;
	string startGameFile;
	string movesFile;
	string movesArr[MAX_MOVES];
	string inputFile[MAX_MOVES];
	int numOfMoves = 0;
	int numOfStartMoves = 0;

public:
	FilesPlayer() : Player() {};
	void setInputFile(string fileName,string moveFile)
	{
		startGameFile = fileName;
		movesFile = moveFile;
		ifstream inFile(startGameFile);
		if (inFile.fail())
		{
			illegalFile = true;
		}
		getPlayerStartMoves(startGameFile);
		if (status != noReason)
			readMovesFile();
	}

	int getnumOfStartMoves()
	{
		return numOfStartMoves;
	}
	int getnumOfMoves()
	{
		return numOfMoves;
	}
	int getErrorLine() const
	{
		return errLine;
	}
	string getCurrLine(string fileName,int rowNum)
	{
		if (fileName == "inputFile")
		{
			return inputFile[rowNum];
		}
		else
		{
			return movesArr[rowNum];
		}
	}
	void readMovesFile();
	
	bool readMove(int moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType,Piece** playerBoard);
	virtual void  getPlayerStartMoves() override;
	void getPlayerStartMoves(string fileName);
	void setFileStatus(Reason reason, Error theError, int line);
	string* parseLine(string line, int& size, int lineNum, Error error);
	bool checkXYInRange(int num, char cord);
	bool checkForCorrectType(const char& type,const int& numOfRow);
	bool checkForCorrectJokerType(const char& type, const int& numOfRow);
	bool checkMoveisLegal(const int& currX, const int& currY, const int& newX, const int& newY);
	bool checkIfPieceCanMove(const char& type, const int& lineNum);
};