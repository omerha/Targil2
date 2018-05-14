#pragma once
#include "io_utils.h"
#include "FilesPlayer.h"
#include "keyBoardPlayer.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#define QUIET_MODE -1
#define SHOWALL_MODE 2
#define TIE 0
#define NUM_OF_PALYERS 2
using namespace std;

class TheGame
{
	int numOfPlayers;
	Player* p[2];
	int winner;
//	Piece gameBoard[N+1][M+1]; //need to check if we actually need this board
	int showMode;
	int delayTime;
	bool showOnlyKnownInfo = false;
	bool over;
	bool consoleGame;
public:
	void init();
	void initStartBoard();
	void run();
	void checkForWinner();
	int pieceFight(Piece p1, Piece p2);
	TheGame() 
	{
		winner = 0;
		numOfPlayers = 2;
		over = false;
		showMode = 2;
		delayTime = 50;
		showOnlyKnownInfo;
	};
	void move(int moveNum);
	void movePiece(const int& oldX, const int& oldY, const int& newX, const int& newY,const int& playerNum,const int& jokerX,const int& jokerY,const char& newJokerType);
	void drawPiece(const int & oldX, const int & oldY, const int & newX, const int & newY, int playerNum, int fightResult);
	void drawGameBoard();
	void createOutputFile();
	void drawBoardToFile(ofstream& outfile);
	void printToScreen(bool start);
	void setShowMode(int whoToShow)// 2 is all 1 is player 2 0 is player 1 and -1 is none aka quiet.
	{
		showMode= whoToShow - 1;
	}
	void setDelayMode(int sDelay)
	{
		delayTime = sDelay;
	}
	void setUnkownInfoMode(bool unkownInfoMode)
	{
		showOnlyKnownInfo = unkownInfoMode;
	}
	void setConsoleGame(bool console)
	{
		consoleGame = console;
	}
	void drawBoardLines();
	void updatePieceAfterFight(int i, int j, int res);
};