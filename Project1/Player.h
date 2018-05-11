#pragma once
#include <string>
#include "Piece.h"
#include "Reason.h"
#include "Error.h"
#include "Color.h"
#define M 10 //colums
#define N 10 // rows
#define K 13 // The num of pieces of each player

#define NUM_OF_ROCK 2
#define NUM_OF_PAPER 5
#define NUM_OF_SCISSORS 1
#define NUM_OF_BOMB 2
#define NUM_OF_JOKER 2
#define NUM_OF_FLAG 1



class Player
{
	friend class TheGame;
	//Piece playerBoard[N+1][M+1];
	
	int counterPieces[6];
	
	//std::string startGameFile; 
//	std::string movesFile; 

//	int errorLine;
	//string movesArr[100];
//	int numOfMoves = 0;
	Color color;
//	FilesPlayer startFile;
//	FilesPlayer moveFile;
protected:
	Reason status;
	Piece** playerBoard;
	Error error;
public:
	Piece** getPlayerBoard() {
		return playerBoard;
	}
	virtual void getPlayerStartMoves() =0;
	void checkValidityiPieces();
	void countPieces(char type);
	void removePiece(int i, int j);
	Player();
	~Player();
	bool move(int moveNum, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType);
	//void movePlayerError(int lineNum);  we need this?
	void setPlayerStatus(Reason reason, Error theError);
	void setColor(Color c) {
		color = c;
	}

	void printError();
	string returnReason();
	void hideJoker();
};