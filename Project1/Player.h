#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
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
#define NUM_OF_MOVING_PIECES 3

class Player
{
	friend class TheGame;
	Color color;
protected:
	int counterPieces[NUM_OF_PIECES_TYPE];
	Reason status;
	Piece** playerBoard;
	Error error;
	int playerNumber;
public:
	Piece** getPlayerBoard() {
		return playerBoard;
	}
	Reason getStatus() {
		return status;
	}
	virtual void getPlayerStartMoves() =0;
	void checkValidityiPieces();
	void countPieces(char type);
	void removePiece(int i, int j);
	Player();
	virtual ~Player();
	virtual bool move(int& moveNum, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType) =0;
	void setPlayerStatus(Reason reason, Error theError);
	void setColor(Color c) {
		color = c;
	}
	bool checkForCorrectJokerType(const char& type);
	bool checkMoveisLegal(const int& currX, const int& currY, const int& newX, const int& newY);
	bool checkXYInRange(int num, char cord);
	virtual void printError()=0;
	string returnReason();
	void hideJoker();
	Error checkIfPieceCanMove(const char& type);
	bool checkForCorrectType(const char& type);
	bool readCurrentMove(string currentLine, Error err, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType);
	Error validateMove(int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation);
	string* parseLine(string line, int& size, Error err);
	bool readCurrentStartLine(string currentLine, Error err, int& lenLine);
};