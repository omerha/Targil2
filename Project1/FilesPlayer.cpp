#include "FilesPlayer.h"
int FilesPlayer::currentNumPlayer = 0;

void FilesPlayer::readMovesFile()
{
	int numOfRows = 0;
	string tmpReadFile;
	ifstream inFile(movesFile);
	if (inFile.fail())
	{
		illegalFile = true;
	}
	while (!inFile.eof() && !illegalFile)
	{
		if (getline(inFile, tmpReadFile))
		{
			if (!(tmpReadFile.empty()))
				movesArr[numOfRows++] = tmpReadFile;
		}
		else
		{
			//setPlayerStatus(badMoves, errorFile, 0);
		}
	}
	numOfMoves = numOfRows;
}

bool FilesPlayer::move(int& moveNum, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType)
{

	if (moveNum < numOfMoves)
	{
		if (!readCurrentMove(movesArr[moveNum], wrongFrormatRowMoveFile, newXLocation, newYLocation, oldXLocation, oldYLocation, jokerXLocation, jokerYLocation, newJokerType))
		{
			if (moveNum == 1)
				errLine = moveNum;
			errLine = moveNum + 1;
			return false;
		}
		return true;
	}
	return false;
}
void FilesPlayer::getPlayerStartMoves()//This function reads the first file and checks for errors in
{
	currentNumPlayer++;
	setInputFile("player"+to_string(currentNumPlayer)+".rps_board", "player" + to_string(currentNumPlayer) + ".rps_moves");
}
void FilesPlayer::getPlayerStartMoves(string fileName)
{
	ifstream inFile(fileName);
	int numOfRows = 0, inputIndex = 0;
	string tmpRead;
	int lenLine = 0;
	if (illegalFile == true)
	{
		setFileStatus(badPosition, notExistFile, 0);
		return;
	}
	while (!inFile.eof() && !illegalFile)
	{
		if (numOfRows > K)
		{
			setFileStatus(badPosition, tooManyRows, numOfRows);
			illegalFile = true;
			return;
		}
		else if (getline(inFile, tmpRead))
		{
			if (!tmpRead.empty())
			{
				numOfRows++;
				
				inputIndex = 0;
			
				if (!readCurrentStartLine(tmpRead, wrongFormatRowInputFile, lenLine))
				{
					if ((inputIndex == 0) && (numOfRows == 1))
					{
						setFileStatus(badPosition, emptyFile, numOfRows); //File is empty 
						return;
					}
					errLine = numOfRows;
					return;
				}
			}
		}
	}
	if (numOfRows == 0)
		setFileStatus(badPosition, wrongFormatRowInputFile, numOfRows); // error input
}

void FilesPlayer::setFileStatus(Reason reason, Error theError, int line)
{
	Player::setPlayerStatus(reason, theError);
	errLine = line;
}







