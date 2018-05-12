#include "TheGame.h"


void TheGame::init()//First function.
{
	//p[i] = new FilesPlayer();
	p[0] = new keyBoardPlayer();
	p[1] = new keyBoardPlayer();
	p[0]->playerNumber = 1;
	p[1]->playerNumber = 2;
	int k;
	bool goodToInitBoard = true;
	if (typeid(*p[0]) == typeid(keyBoardPlayer))
		k = 2; //it's need to be K
	else k = 1;

	for (int j = 0; j < k; j++)
	{
		for (int i = 0; i < this->numOfPlayers; i++)
		{

			p[i]->getPlayerStartMoves();
			/*if (p[i]->status == noReason) // NO Bad Positioning input file for player <player> - line <bad line number>
			{
				p[i]->checkValidityiPieces();
				if (p[i]->status != noReason)
					goodToInitBoard = false;
				if (showOnlyKnownInfo)
					p[i]->hideJoker();
			}
			else
				goodToInitBoard = false;*/
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
				setFightResult(res, i, j);
			}
			//else if (p[0].playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			//	this->gameBoard[i][j].setPieceType(p[0].playerBoard[i][j].getPieceType());
			//else if (p[1].playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			//	this->gameBoard[i][j].setPieceType(p[1].playerBoard[i][j].getPieceType());

		}
	}
	
}

int TheGame::pieceFight(Piece p1, Piece p2)
{  // The function gets two objects of Pieces and returns 0 if a tie, 1 if the first player wins, and 2 if the second player wins
	if (p1 == p2)
		return 0;
	else if (p1 > p2)
		return 1;
	else 
		return 2;	
}

void TheGame::updatePieceAfterFight(int i, int j, int res)
{
	if (res == 0)
	{
		p[0]->removePiece(i, j);
		p[1]->removePiece(i, j);
		return;
	}
	
	else if (res == 1)
	{
		p[1]->removePiece(i, j);
		return;
	}
	else if (res == 2)
	{
		p[0]->removePiece(i, j);
		return;
	}

}

void TheGame::setFightResult(int fightResult, int xLoc, int yLoc)//Recevies fight result and updates all board accordindly.
{
	if (fightResult == 0) //It means that both players lost
	{
	//	gameBoard[xLoc][yLoc].setPieceType(EMPTY_PIECE);
		p[0]->playerBoard[xLoc][yLoc].setPieceType(EMPTY_PIECE);
		p[0]->playerBoard[xLoc][yLoc].setPieceJoker(false);
		p[1]->playerBoard[xLoc][yLoc].setPieceType(EMPTY_PIECE);
		p[1]->playerBoard[xLoc][yLoc].setPieceJoker(false);
	//	gameBoard[xLoc][yLoc].setPieceJoker(false);
	
	}
	if (fightResult == 1) ///It means that player 1 wins in this square
	{
		//gameBoard[xLoc][yLoc].setPieceType(p[0].playerBoard[xLoc][yLoc].getPieceType());
		//gameBoard[xLoc][yLoc].setPieceJoker(p[0].playerBoard[xLoc][yLoc].getPieceJoker());
		p[1]->playerBoard[xLoc][yLoc].setPieceType(EMPTY_PIECE);
		p[1]->playerBoard[xLoc][yLoc].setPieceJoker(false);
	}
	else if (fightResult == 2) //It means that player 2 wins in this square
	{
		//gameBoard[xLoc][yLoc].setPieceType(p[1].playerBoard[xLoc][yLoc].getPieceType());
		//gameBoard[xLoc][yLoc].setPieceJoker(p[1].playerBoard[xLoc][yLoc].getPieceJoker());
		p[0]->playerBoard[xLoc][yLoc].setPieceType(EMPTY_PIECE);
		p[0]->playerBoard[xLoc][yLoc].setPieceJoker(false);
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
			for (i = 0; i <= 3; i++)
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
				winner = 0;
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
	if (start&& showMode != QUIET_MODE)
		gotoxy(1, 25);
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
		if (showMode != QUIET_MODE)
		drawGameBoard();
	}
	while (!over)
	{
		move(moveNum++);
	}
	printToScreen(start);
	createOutputFile();
}

void TheGame::move(int moveNum)
{
	int i;
	int newX = 0, newY = 0, oldX = 0, oldY = 0, jokerX = 0, jokerY = 0;
	char newJokerType = EMPTY_PIECE;
	if (typeid(*p[0]) == typeid(FilesPlayer)) {
		if ((((FilesPlayer*)p[0])->getnumOfMoves() < moveNum) && (((FilesPlayer*)p[1])->getnumOfMoves() < moveNum))
		{
			over = true;
			p[0]->status = p[1]->status = moveFilesDone;
		}
	}
	for (i = 0; i < numOfPlayers && !over; i++)
	{
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
		setFightResult(fightRes, newX, newY);
	}
	if (newJokerType != EMPTY_PIECE || p[playerNum]->playerBoard[oldX][oldY].getPieceJoker())
	{
		if (p[playerNum]->playerBoard[oldX][oldY].getPieceJoker())
		{
			p[playerNum]->playerBoard[oldX][oldY].setPieceJoker(false);
			if (playerNum == fightRes - 1 || fightRes == -1)
			{
				p[playerNum]->playerBoard[newX][newY].setPieceJoker(true);
		//		gameBoard[newX][newY]->setPieceJoker(true);
				if (newX == jokerX && newY == jokerY)
				{
					p[playerNum]->playerBoard[newX][newY].setPieceType(newJokerType);
			//		gameBoard[newX][newY].setPieceType(newJokerType);
				}
			}
		}
		else {
			//p[playerNum]->playerBoard[jokerX][jokerY].setPieceJoker(true);
			p[playerNum]->playerBoard[jokerX][jokerY].setPieceType(newJokerType);
			//gameBoard[jokerX][jokerY]->setPieceType(newJokerType);
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



void TheGame::createOutputFile()
{
	//ofstream outfile("output.txt");
	//if (outfile.is_open())
	//{
	//	outfile << "Winner: " << winner << "\n";
	//	outfile << "Reason: " ;
	//	if (winner == 1)
	//	{
	//		outfile << p[1]->returnReason();
	//		if (p[1]->status>2)
	//			outfile  <<"for player 2 ";
	//		if (p[1]->errorLine!=0)
	//		{
	//			outfile << "line " << p[1]->errorLine;
	//		}
	//	}
	//	else if (winner == 2)
	//	{
	//		outfile << p[0]->returnReason();
	//		if (p[0]->status>2)
	//			outfile << "for player 1 ";
	//		if (p[0]->errorLine!=0)
	//		{
	//			outfile << "line " << p[0]->errorLine;
	//		}
	//	}
	//	else if (winner == 0)
	//	{
	//		if (p[0]->status == p[1]->status)
	//		{
	//			if (p[0]->status==badPosition)
	//				outfile << "Bad Positioning input files for both players- player 1: line " << p[0]->errorLine << ", player 2: line " << p[1]->errorLine;
	//			if ((p[0]->status == moveFilesDone) || (p[0]->status==flagsCaptured) || (p[0]->status==allEaten))
	//				outfile << "A tie - both Moves input files done without a winner";
	//		}
	//		else
	//		{
	//			outfile << p[0]->returnReason();
	//			if (p[0]->errorLine != 0)
	//			{
	//				outfile << " player 1 line " << p[0]->errorLine;
	//			}
	//			outfile << " and "<< p[1]->returnReason();
	//			if (p[1]->errorLine != 0)
	//			{
	//				outfile << " player 2 line " << p[1]->errorLine;
	//			}
	//		}
	//	}
	//	outfile << "\n\n";
	//	if ((p[0]->status != badPosition) && (p[1]->status != badPosition))
	//	{
	//		drawBoardToFile(outfile);
	//	}
	//	outfile.close();
	//}
	//else {
	//	gotoxy(1, 28);
	//	cout << "can't Create ouput file";

	//}
}
void TheGame::drawBoardToFile(ofstream& outfile)
{
	for (int j = 1; j < 11; j++)
			{
				outfile << "|";
				for (int i = 1; i < 11; i++)
				{
					if (p[0]->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
					{
						if (p[0]->playerBoard[i][j].getPieceJoker())
							outfile << " " << 'j' << "  |";
						else
							outfile << " " << (char)(p[0]->playerBoard[i][j].getPieceType()+32) << "  |";
					}
					else if (p[1]->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
					{
						if (p[1]->playerBoard[i][j].getPieceJoker())
							outfile << " " << JOKER << "  |";
						else
							outfile << " " << p[1]->playerBoard[i][j].getPieceType() << "  |";
					}
					else
						outfile << "    |";
				}
				outfile << "\n";
			}
}
void TheGame::drawBoardLines()
{
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



