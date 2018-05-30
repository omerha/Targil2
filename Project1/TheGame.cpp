#include "TheGame.h"


void TheGame::init()//First function.
{
	int k;
	bool goodToInitBoard = true;
	if (consoleGame == true)
	{
		p[0] = new keyBoardPlayer();
		p[1] = new keyBoardPlayer();
		k = K; 
	}
	else 
	{
		k = 1;
		p[0] = new FilesPlayer();
		p[1] = new FilesPlayer();
	}
	p[0]->playerNumber = 1;
	p[1]->playerNumber = 2;
	for (int j = 0; j < k; j++)
	{
		for (int i = 0; i < this->numOfPlayers; i++)
		{

			p[i]->getPlayerStartMoves();
		}
	}
	for (int i = 0; i < this->numOfPlayers; i++)
	{
		if (p[i]->status == noReason) // NO Bad Positioning input file for player <player> - line <bad line number>
		{
		p[i]->checkValidityiPieces();
		if (p[i]->status != noReason)
		goodToInitBoard = false;
		if (showOnlyKnownInfo)
		p[i]->hideJoker();
		}
		else
		goodToInitBoard = false;
	}


	p[0]->setColor(YELLOW);
	p[1]->setColor(RED);

	if (goodToInitBoard)
		initStartBoard();
}

void TheGame::initStartBoard()
{ // The function places the tools of the two players on the board, 
	//if there are two tools on the same slot check who is stronger and flatten the other

	int i, j, res;
	for (i = 1; i <= N; i++)
	{
		for (j = 1; j <= M; j++)
		{
			if ((p[0]->playerBoard[i][j].getPieceType() != EMPTY_PIECE) && (p[1]->playerBoard[i][j].getPieceType() != EMPTY_PIECE))
			{
				
				res = pieceFight(p[0]->playerBoard[i][j], p[1]->playerBoard[i][j]);
				updatePieceAfterFight(i, j, res);
			}
		}
	}
	
}

int TheGame::pieceFight(Piece p1, Piece p2)
{  // The function gets two objects of Pieces and returns 0 if a tie, 1 if the first player wins, and 2 if the second player wins
	if (p1 == p2)
		return TIE;
	else if (p1 > p2)
		return 1;
	else if (p1 < p2)
		return 2;	
}

void TheGame::updatePieceAfterFight(int i, int j, int res)
{
	if (res == TIE)
	{
		p[0]->removePiece(i, j);
		p[1]->removePiece(i, j);
		return;
	}
	
	else if (res == 1)
	{
		p[0]->playerBoard[i][j].setRevealType(true);
		p[1]->removePiece(i, j);
		return;
	}
	else if (res == 2)
	{
		p[1]->playerBoard[i][j].setRevealType(true);
		p[0]->removePiece(i, j);
		return;
	}

}

void TheGame::checkForWinner() 
{
	int i,  numPlayer, counter = 0;
	for (numPlayer = 0; numPlayer < numOfPlayers; numPlayer++)
	{
		if (p[numPlayer]->status != noReason)
		{
			over = true;
		}
		else
		{
			counter = 0;
			for (i = 0; i <= NUM_OF_MOVING_PIECES; i++)//checking moving pieces
			{
				counter += p[numPlayer]->counterPieces[i];
			}
			if (counter == 0)
			{
				p[numPlayer]->status = allEaten;
				over = true;

			}
			if (p[numPlayer]->counterPieces[F] == 0)
			{
				p[numPlayer]->status = flagsCaptured;
				over = true;
			}
		}
	}
	if (over)
	{
		if ((p[0]->status != noReason) && (p[1]->status != noReason))
		{
			if ((p[0]->status == flagsCaptured) && (p[1]->status != flagsCaptured))
				winner = 2;
			else if ((p[1]->status == flagsCaptured) && (p[0]->status != flagsCaptured))
				winner = 1;
			else 
				winner = TIE;
		}
		if (p[0]->status == noReason)
		{
			winner = 1;
		}
		if (p[1]->status == noReason)
		{
			winner = 2;
		}
	}
}

void TheGame::printToScreen(bool start)
{
	int i;
	if (consoleGame)
		system("cls");

	if (start&& showMode != QUIET_MODE&&!consoleGame)
		gotoxy(1, 25);
	if (winner == 0)
		cout << "The game ended in a tie" << endl;
	else
		cout << "The winner is player " << winner << endl;
	setTextbBackground(RED);
	setTextColor(WHITE);
	for (i = 0; i < numOfPlayers; i++)
	{
		cout << "\nThe Errors of player number " << i + 1 << ": ";
		p[i]->printError();
	}
}

void TheGame::run()
{
	int moveNum = 0;
	bool start = false;
	init();
	checkForWinner();
	if ((p[0]->status!=badPosition)&& (p[1]->status != badPosition))
	{
		start = true;
		if (showMode != QUIET_MODE && !consoleGame)
		{
			drawGameBoard();
		}

	}
	while (!over)
	{
		move(moveNum++);
	}
	if (typeid(*p[0]) == typeid(FilesPlayer))
		((FilesPlayer*)p[0])->createOutputFile(p, winner);
	printToScreen(start);

}

TheGame::~TheGame()
{
	for (int i = 0; i < numOfPlayers; i++) {
		delete[] p[i];
	}
}

void TheGame::move(int moveNum)
{
	int i;
	int newX = 0, newY = 0, oldX = 0, oldY = 0, jokerX = 0, jokerY = 0;
	char newJokerType = EMPTY_PIECE;
	int secondPlayerIndex;
	if (typeid(*p[0]) == typeid(FilesPlayer)) {
		if ((((FilesPlayer*)p[0])->getnumOfMoves() < moveNum) && (((FilesPlayer*)p[1])->getnumOfMoves() < moveNum))
		{
			over = true;
			p[0]->status = p[1]->status = moveFilesDone;
		}
	}
	for (i = 0; i < numOfPlayers && !over; i++)
	{
		secondPlayerIndex = abs(i - 1);
		if (consoleGame == true ||  (showMode == i ))
		{
			
				drawGameBoardForSinglePlayer(i, secondPlayerIndex);
		}
		newJokerType = EMPTY_PIECE;
		if (p[i]->move(moveNum, newX, newY, oldX, oldY, jokerX, jokerY, newJokerType))
		{
			movePiece(oldX, oldY, newX, newY, i,jokerX,jokerY,newJokerType);
		}
			checkForWinner();
	}
}

void TheGame::movePiece(const int & oldX, const int & oldY, const int & newX, const int & newY,const int& playerNum, const int& jokerX, const int& jokerY, const char& newJokerType)
{
	
	int secondPlayerIndex = abs(playerNum - 1);
	int fightRes = -1;
	if(p[secondPlayerIndex]->playerBoard[newX][newY].getPieceType() != EMPTY_PIECE)
	{
		fightRes = pieceFight(p[0]->playerBoard[newX][newY], p[1]->playerBoard[newX][newY]);
		updatePieceAfterFight(newX, newY, fightRes);
	}
	if (newJokerType != EMPTY_PIECE || p[playerNum]->playerBoard[oldX][oldY].getPieceJoker())
	{
		if (p[playerNum]->playerBoard[oldX][oldY].getPieceJoker())
		{
			p[playerNum]->playerBoard[oldX][oldY].setPieceJoker(false);
			if (playerNum == fightRes - 1 || fightRes == -1)
			{
				p[playerNum]->playerBoard[newX][newY].setPieceJoker(true);
				if (newX == jokerX && newY == jokerY)
				{
					p[playerNum]->playerBoard[newX][newY].setPieceType(newJokerType);
				}
			}
		}
		else {
			p[playerNum]->playerBoard[jokerX][jokerY].setPieceType(newJokerType);
			if (showMode == SHOWALL_MODE || showMode == playerNum && !showOnlyKnownInfo)
				p[playerNum]->playerBoard[jokerX][jokerY].drawPiece(p[playerNum]->color, jokerX, jokerY);
		}
	}
	if (showMode != QUIET_MODE)
	{
		Sleep(delayTime);
		drawPiece(oldX, oldY, newX, newY, playerNum,fightRes);
	}
}

void TheGame::drawPiece(const int & oldX, const int & oldY, const int & newX, const int & newY, int playerNum,int fightResult)
{
	int secondPlayerIndex = abs(playerNum -1);
	if (showMode == SHOWALL_MODE)
	{
		if (fightResult != -1) {
			if (fightResult == TIE)
			{
				p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
				p[secondPlayerIndex]->playerBoard[newX][newY].removePiece(newX, newY);
			}
			else if (fightResult - 1 == playerNum)
			{
				p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
				p[playerNum]->playerBoard[newX][newY].drawPiece(p[playerNum]->color, newX, newY);
			}
			else
			{
				p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
			}
		}
		else
		{
			p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
			if (showOnlyKnownInfo)
				p[playerNum]->playerBoard[newX][newY].drawUnknownPiece(p[playerNum]->color, newX, newY);
			else
				p[playerNum]->playerBoard[newX][newY].drawPiece(p[playerNum]->color, newX, newY);
		}
	}
	else if (showMode == playerNum)
	{
		if (fightResult != -1) {
			if (fightResult - 1 == playerNum)
			{
				p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
				p[playerNum]->playerBoard[newX][newY].drawPiece(p[playerNum]->color, newX, newY);
			}
			else
			{
				p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
			}
		}
		else
		{
			p[playerNum]->playerBoard[oldX][oldY].removePiece(oldX, oldY);
			if (showOnlyKnownInfo)
				p[playerNum]->playerBoard[newX][newY].drawUnknownPiece(p[playerNum]->color, newX, newY);
			else
				p[playerNum]->playerBoard[newX][newY].drawPiece(p[playerNum]->color, newX, newY);
		}
	}
	else {
		if (!(fightResult - 1 == secondPlayerIndex))
		{
			p[secondPlayerIndex]->playerBoard[newX][newY].removePiece(newX, newY);
		}
	}
}

void TheGame::drawGameBoard()
{
	drawBoardLines();
	int player = showMode != 1 ? 0 : 1;
	int maxPlayerToPrint = showMode >= 1 ? numOfPlayers : 1;
	for (; player < maxPlayerToPrint; player++) {
		for (int i = 1; i <= N; i++)
		{
			for (int j =1; j <= M; j++)
			{
				if (p[player]->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
				{
					if (showOnlyKnownInfo)
						p[player]->playerBoard[i][j].drawUnknownPiece(p[player]->color, i, j);
					else
						p[player]->playerBoard[i][j].drawPiece(p[player]->color, i, j);
				}
			}
		}
	}
}

void TheGame::drawGameBoardForSinglePlayer(int currentPlayer, int unknownPlayer)
{
	drawBoardLines();
	
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= M; j++)
		{
			if (p[currentPlayer]->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			{
				p[currentPlayer]->playerBoard[i][j].drawPiece(p[currentPlayer]->color, i, j);
			}
			else if(p[unknownPlayer]->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			{
				p[unknownPlayer]->playerBoard[i][j].drawUnknownPiece(p[unknownPlayer]->color, i, j);
			}
		}
	}
	
}

void TheGame::drawBoardLines()
{
	setTextColor(WHITE);
	system("cls");
	for (int j = 1; j < 11; j++)
	{
		for (int i = 1; i < 11; i++)
		{
			p[0]->playerBoard[i][j].removePiece(i, j);
			if (j == 1)
			{
				gotoxy(i * 3 + 3, 4);
				cout << i;
			}
			gotoxy(i * 3 +2, j * 2 +3);
			cout << "|";
			gotoxy(i * 3 +5, j * 2+3);
			cout << "|";
		}
		gotoxy(3, j * 2 +3);
		cout << j;
	}
}



