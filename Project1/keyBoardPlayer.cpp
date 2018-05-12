#include "keyBoardPlayer.h"
#define _CRT_SECURE_NO_WARNINGS

void keyBoardPlayer::getPlayerStartMoves()
{
	char tmpLine[9];
	char jokerTypeTmp[2];
	int i;
	bool next = false;
	while (!next)
	{
		cout << "Player " << playerNumber << " please insert piece type and the coordinates to locate the piece on the board\n";
		//getline(cin, tmpLine2);
		cin.getline(tmpLine, 9);
		//cout << tmpLine<<endl;
		if (tmpLine[0] == 'J')
		{
			cout << "Please insert the initial representation for the joker\n";
			cin.getline(jokerTypeTmp, 2);
			//cout << jokerTypeTmp << endl;
			strcat_s(tmpLine,7, " ");
			strcat_s(tmpLine,9, jokerTypeTmp);
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
	char tmpLine[16];
	bool next = false;
	while (!next)
	{
		cout << "Player " << playerNumber << " please enter your move\n";
		cin.getline(tmpLine, 16);

		next = readCurrentMove(tmpLine, wrongFrormatRowMoveFile, newXLocation, newYLocation, oldXLocation, oldYLocation, jokerXLocation, jokerYLocation, newJokerType);
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
