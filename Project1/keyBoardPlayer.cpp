#include "keyBoardPlayer.h"

void keyBoardPlayer::getPlayerStartMoves()
{
	int i;
	for (i = 0; i < K; i++)
	{
		keyBoardInput();
	}

	
}

bool keyBoardPlayer::move(int & moveNum, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType)
{
	return false;
}

void keyBoardPlayer::keyBoardInput()
{

	string tmpLine2;
	char tmpLine[6];
	char jokerTypeTmp[2];
	int i,j, playerNumber, pieceNumber;
	bool next = false;
	for (i = 0; i < K; i++)
	{
		for (j = 0; j < 2; j++)
		{
			next = false;
			while (!next)
			{
				cout << "Player "<< j+1 <<" please insert piece type number "<< i+1 << " and the coordinates to locate the poece on the board\n";
				getline(cin, tmpLine2);
				//cout << tmpLine2;
				if (tmpLine[0] == 'J')
				{
					cout << " Please insert the initial representation of the joker\n";
					cin >> jokerTypeTmp;
					//strcat(tmpLine, " ");
					//strcat(tmpLine, jokerTypeTmp);
				}
				next= readCurrentStartLine(tmpLine, wrongFormatRowInputConsole, i);
				if (!next)
					cout << "Wrong input format row \n";
			}
		}
	}

}
