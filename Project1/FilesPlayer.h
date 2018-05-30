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
	ifstream inFile;
	string startGameFile;
	string movesFile;
	string movesArr[MAX_MOVES];
	string inputFile[MAX_MOVES];
	int numOfMoves = 0;
	int numOfStartMoves = 0;
	int currentMove = 0;
public:
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
		if (status == noReason)
			readMovesFile();
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
	virtual bool move(int& moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType) override;
	virtual void  getPlayerStartMoves() override;
	void getPlayerStartMoves(string fileName);
	void setFileStatus(Reason reason, Error theError, int line);
	virtual void printError() override;
	void createOutputFile(Player** p,int winner);
	void drawBoardToFile(ofstream& outfile, Player** p);
	
};