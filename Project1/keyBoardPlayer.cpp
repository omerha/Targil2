#include "keyBoardPlayer.h"


void keyBoardPlayer::getPlayerStartMoves()
{
	int i;
	bool next = false;
	string tmpLine, jokerTypeTmp;
	while (!next)
	{
		cout << "Player " << playerNumber << " please insert piece type and the coordinates to locate the piece on the board\n";

		getline(cin, tmpLine);
		while (tmpLine.empty())
			getline(cin, tmpLine);
		if (tmpLine[0] == 'J')
		{
			cout << "Please insert the initial representation for the joker" << endl;
			getline(cin, jokerTypeTmp);
			while (jokerTypeTmp.empty())
				getline(cin, jokerTypeTmp);
			tmpLine = tmpLine + " " + jokerTypeTmp;
			//cout << tmpLine << endl;
		}
		next = readCurrentStartLine(tmpLine, wrongFormatRowInputConsole, i);
		if (!next)
		{
			printError();
			status = noReason;
			error = noError;
		}
	}
}

bool keyBoardPlayer::move(int & moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType)
{
	char isJokerChange;
	string tmpLine, tmpLine2, tmpLine3;
	bool next = false;
	int x = 0, y = 0;
	while (!next)
	{
		//gotoxy(37, 3 + playerNumber * 2);
		gotoxy(0, 25);
		setTextColor(WHITE);
		cout << "Player " << playerNumber << " please enter your move " << endl;
		getline(cin, tmpLine);
		while (tmpLine.empty())
			getline(cin, tmpLine);
		if (counterPieces[J] >= 1)
		{
			cout << "Player " << playerNumber << " do you wants to change the joker representation? (Y/N) " << endl;
			isJokerChange = getchar();
			if ((isJokerChange == 'Y') || (isJokerChange == 'y'))
			{
				if (counterPieces[J] > 1)
				{
					cout << "Player " << playerNumber << " which joker do you want to change? " << endl;
					getline(cin, tmpLine2);
					while (tmpLine2.empty())
						getline(cin, tmpLine2);
				}
				else // there is just 1 joker alive
				{
					findJoker(x, y);
					tmpLine2 = to_string(x) + " " + to_string(y);
				}
				cout << "Player " << playerNumber << " to which represent you want to change the joker? " << endl;

				getline(cin, tmpLine3);
				while (tmpLine3.empty())
					getline(cin, tmpLine3);
				tmpLine = tmpLine + " J: " + tmpLine2 + " " + tmpLine3;
				//cout << tmpLine << endl;
			}
		}


		cout << "\r" << flush;
		next = readCurrentMove(tmpLine, wrongFrormatRowMoveFile, newXLocation, newYLocation, oldXLocation, oldYLocation, jokerXLocation, jokerYLocation, newJokerType);
		if (oldXLocation == jokerXLocation && oldYLocation == jokerYLocation)
		{
			jokerXLocation = newXLocation;
			jokerYLocation = newYLocation;
		}
		if (!next)
		{
			printError();
			status = noReason;
			error = noError;
		}
	}
	return true;
}

void keyBoardPlayer::printError()
{
	switch (error)
	{
	case 1:
		if (status == badPosition)
			cout << "The coordinates are not in the range of the board\n";
		else
			cout << "The coordinates are not in the range of the board\n";
		break;
	case 2:
		if (status == badPosition)
			cout << "The coordinates already have a piece in the board\n";
		else
			cout << "There is a piece in the place that inserted \n";
		break;
	case 3:
		cout << "Too many pieces of the same type were inserted\n";
		break;
	case 4:
		cout << "No flag was inserted\n";
		break;
	case 5:
		cout << "Unknown piece was inserted \n";
		break;
	case 6:
		break;
	case 7:
		cout << "The format of the line is invalid\n";
		break;
	case 8:
		cout << "The format of the line is invalid\n";
		break;
	case 9:
		cout << "There is no piece in the place that inserted \n";
		break;
	case 10:
		cout << "Joker does not exist in the place that inserted \n";
		break;
	case 11:
		cout << "Joker has changed into a piece that didn't exist  \n";
		break;
	case 12:
		break;
	case 13:
		cout << "Move a piece in an illegal way  \n";
		break;
	case 14:
		break;
	case 15:
		cout << "Unknow piece was inserted for joker \n";
		break;
	case 16:
		cout << "The coordinates of the joker are not in the range of the board\n";
		break;
	case 17:
		cout << "The bomb can't move\n";
		break;
	case 18:
		cout << "The flag can't move\n";
		break;
	case 19:
		break;

	case 20:
		cout << "Wrong format row\n";
		break;
	case 21:
		cout << "Wrong format row\n";
		break;
	default:
		if (status == allEaten)
			cout << "All the moving pieces were eaten\n";
		else if (status == flagsCaptured)
			cout << "All the flags were caught\n";
		else if (status == moveFilesDone)
			cout << " The player's moves have ended";
		else
			cout << "There are no errors for this player\n";
		break;
	}
}

void keyBoardPlayer::findJoker(int & x, int & y)
{
	int i, j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (playerBoard[i + 1][j + 1].getPieceJoker())
			{
				x = i + 1;
				y = j + 1;
				return;
			}

		}
	}
}
