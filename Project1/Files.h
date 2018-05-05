#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include "Error.h"
#include "Reason.h"
#include "Piece.h"
#define M 10 //colums
#define N 10 // rows
#define K 13 // The num of pieces of each player
#define MAX_MOVES 100
using namespace std;
class Files {
	bool illegalFile = false;
	int errLine = NULL;
	Error error = noError;
	Reason fileStatus = noReason;
	ifstream inFile;
	string movesArr[MAX_MOVES];
	string inputFile[MAX_MOVES];
	int numOfMoves = 0;
	int numOfStartMoves = 0;
public:
	void setInputFile(string fileName,Piece** playerBoard) 
	{
	ifstream inFile(fileName);
		if (inFile.fail())
		{
			illegalFile = true;
		}
		readFromFile(fileName, playerBoard);
	}
	void setMoveFile(string fileName)
	{
		ifstream inFile(fileName);
		if (inFile.fail())
		{
			illegalFile = true;
		}
		readMovesFile(fileName);
	}
	int getnumOfStartMoves()
	{
		return numOfStartMoves;
	}
	int getnumOfMoves()
	{
		return numOfMoves;
	}
	Reason getFileStatus  ()const
	{
		return fileStatus;
	}
	Error getFileError() const
	{
		return error;
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
	void readMovesFile(string fileName);
	
	bool readMove(int moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType,Piece** playerBoard);

	void readFromFile(string fileName, Piece** playerBoard);
	void setFileStatus(Reason reason, Error theError, int line);
	string* parseLine(string line, int& size, int lineNum, Error error);
	bool checkXYInRange(int num, char cord);
	bool checkForCorrectType(const char& type,const int& numOfRow);
	bool checkForCorrectJokerType(const char& type, const int& numOfRow);
	bool checkMoveisLegal(const int& currX, const int& currY, const int& newX, const int& newY);
	bool checkIfPieceCanMove(const char& type, const int& lineNum);
};