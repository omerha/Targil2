#pragma once
#include "Player.h"
#include <string>
#include <string.h>
#include <iostream>
using namespace std;

class keyBoardPlayer : public Player
{
public:
	virtual void  getPlayerStartMoves() override;
	virtual bool move(int& moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType) override;
	virtual void printError() override;
};