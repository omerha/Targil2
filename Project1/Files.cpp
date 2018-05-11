#include "FilesPlayer.h"


void FilesPlayer::readMovesFile(string fileName)
{
	int numOfRows = 0;
	string tmpReadFile;
	ifstream inFile(fileName);
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

bool FilesPlayer::readMove(int moveNum, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType, Piece** playerBoard)
{

	//This functino reads the move files and check for erros.
	int xJoker, yJoker;
	string* currInput = nullptr;
	int numOfIndex = 0;
	char nJokerType;
	int currX = 0, currY = 0, newX = 0, newY = 0;
	if (moveNum < numOfMoves)
	{
		currInput = parseLine(movesArr[moveNum], numOfIndex, moveNum, wrongFrormatRowMoveFile);
		if (numOfIndex < 4 || numOfIndex>8)
		{
			setFileStatus(badMoves, wrongFrormatRowMoveFile, moveNum); //error - too many or too few arguments in line.
			return false;
		}
		if (isdigit(currInput[0][0]) && isdigit(currInput[1][0]) && isdigit(currInput[2][0]) && isdigit(currInput[3][0]))
		{
			currX = stoi(currInput[0]);
			currY = stoi(currInput[1]);
			newX = stoi(currInput[2]);
			newY = stoi(currInput[3]);
		}
		else
		{
			setFileStatus(badMoves, wrongFrormatRowMoveFile, moveNum + 1);
			return false;
		}
		if (playerBoard[newX][newY].getPieceType() != EMPTY_PIECE)
		{
			setFileStatus(badMoves, sameLocation, moveNum + 1);
			return false;
		}
		if (!(checkXYInRange(currX, 'X') && checkXYInRange(newX, 'X') && checkXYInRange(newY, 'Y') && checkXYInRange(currY, 'Y')))
		{
			setFileStatus(badMoves, notInRange, moveNum + 1); //error x y not in range.
			return false;
		}
		if (checkMoveisLegal(currX, currY, newX, newY)) // move more than on square
		{
			setFileStatus(badMoves, moveIllegal, moveNum + 1);
			return false;
		}
		if (!(checkIfPieceCanMove(playerBoard[currX][currY].getPieceType(), moveNum + 1)))
		{
			return false;
		}

		if (numOfIndex > 6)//means there is a move for the joker. 
		{
			if (currInput[4].length() == 2)
			{
				if (currInput[4][0] == JOKER)
				{
					if (isdigit(currInput[5][0]) && isdigit(currInput[6][0]))
					{
						xJoker = stoi(currInput[5]);
						yJoker = stoi(currInput[6]);
					}
					else
					{
						setFileStatus(badMoves, wrongInputJoker, moveNum + 1);
						return false;
					}
					nJokerType = currInput[7][0];
					if (!(checkXYInRange(xJoker, 'X') && checkXYInRange(yJoker, 'Y')))//Something is wrong with joker xy coordinates
					{
						setFileStatus(badMoves, jokerNotInRange, moveNum + 1);
						return false;
					}
					else if (playerBoard[xJoker][yJoker].getPieceJoker() || (playerBoard[currX][currY].getPieceJoker() && xJoker == newX && yJoker == newY))
					{
						if (!(checkForCorrectJokerType(nJokerType, moveNum+1)))
							return false;
						else
						{
							jokerXLocation = xJoker;
							jokerYLocation = yJoker;
							newJokerType = nJokerType;
						}
					}
					else
					{
						setFileStatus(badMoves, notExistJoker, moveNum + 1); //Error- not exit joker in this location
						return false;
					}
				}
				else //The wrong is for example: "K:" insted of "J:"
				{
					setFileStatus(badMoves, wrongFrormatRowMoveFile, moveNum + 1);
					return false;
				}
			}
			else //The wrong, for example: "J::" insted of "J:"
			{
				setFileStatus(badMoves, wrongFrormatRowMoveFile, moveNum + 1);
				return false;
			}
		}
		playerBoard[newX][newY].setRevealType(playerBoard[currX][currY].getRevealType());
		playerBoard[newX][newY].setPieceType(playerBoard[currX][currY].getPieceType());
		playerBoard[currX][currY].setPieceType(EMPTY_PIECE);
		oldXLocation = currX;
		oldYLocation = currY;
		newXLocation = newX;
		newYLocation = newY;
		return true;
	}
	delete[] currInput;
}

void FilesPlayer::readFromFile(string fileName, Piece** playerBoard)
{
	ifstream inFile(fileName);
	int numOfRows = 0, inputIndex = 0;
	string tmpRead;
	string* getInput = nullptr;
	int xLocation, yLocation;
	char type;
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
				getInput = parseLine(tmpRead, inputIndex, numOfRows, wrongFormatRowInputFile);
				if ((inputIndex == 3) || (inputIndex == 4))
				{
					type = getInput[0][0];
					if (isdigit(getInput[1][0]) && isdigit(getInput[2][0]))
					{
						xLocation = stoi(getInput[1]);
						yLocation = stoi(getInput[2]);
					}
					else
					{
						setFileStatus(badPosition, wrongFormatRowInputFile, numOfRows);
						return;
					}
					if (!(checkXYInRange(yLocation, 'Y') && checkXYInRange(xLocation, 'X')))
					{
						setFileStatus(badPosition, notInRange, numOfRows);
						return;
					}
					if (playerBoard[xLocation][yLocation].getPieceType() != EMPTY_PIECE)// There is a piece in this location
					{
						setFileStatus(badPosition, sameLocation, numOfRows);
						return;
					}
				}
				else
				{
					if (inputIndex) {
						setFileStatus(badPosition, wrongFormatRowInputFile, numOfRows); // the length line isn't 3 or 4 chars
						return;
					}
				}
				if (inputIndex == 4)
				{
					if (getInput[0][0] == JOKER)
					{
						type = getInput[3][0];
						if(!(checkForCorrectJokerType(type,numOfRows)))
							return;					
					}
					else
					{
						setFileStatus(badPosition, wrongFormatRowInputFile, numOfRows);
						return;
					}
				}
				else if (inputIndex == 3)
				{
					if (!(checkForCorrectType(type, numOfRows)))
						return;

				}
				if ((inputIndex == 0) && (numOfRows == 1))
				{
					setFileStatus(badPosition, emptyFile, numOfRows); //File is empty 
					return;
				}
				inputFile[numOfRows - 1] = tmpRead;
				delete[] getInput;
			}
		}
	}
	if (numOfRows == 0)
		setFileStatus(badPosition, wrongFormatRowInputFile, numOfRows); // error input
	numOfStartMoves = numOfRows;
}

void FilesPlayer::setFileStatus(Reason reason, Error theError, int line)
{
	fileStatus = reason;
	error = theError;
	errLine = line;
}

string * FilesPlayer::parseLine(string line, int & size, int lineNum, Error error)
{
	string tmpRead, temp;
	istringstream tempCh(line);
	int inputIndex = 0;
	string getInput[20] = { "0" };
	while (getline(tempCh, temp, ' '))
	{
		if (!(temp.empty()))
			getInput[inputIndex++] = temp;
	}
	if (inputIndex)
	{
		string* out = new string[inputIndex];
		for (int i = 0; i < inputIndex; i++)
		{
			if (getInput[i].length() >= 2)
			{
				if (getInput[i].length() > 2 || (!(isdigit(getInput[i][0]) && isdigit(getInput[i][1])) && getInput[i][0] != JOKER))
					setFileStatus(badPosition, wrongFormatRowInputFile, lineNum);
			}
			else if (getInput[i].empty())
				setFileStatus(badPosition, wrongFormatRowInputFile, lineNum);
			out[i] = getInput[i];
		}
		size = inputIndex;
		return out;
	}
	else
		return nullptr;
}


bool FilesPlayer::checkXYInRange(int num, char cord)
{
	if (cord == 'X')
	{
		if (num < 1 || num>10) // X coordinate isn't inrange
		{
			return false;
		}
	}
	if (cord == 'Y')
	{
		if (num < 1 || num>10) // X coordinate isn't inrange
		{
			return false;
		}
	}
	return true;
}

bool FilesPlayer::checkForCorrectType(const char& type,const int& numOfRow)
{
	if ((type != ROCK) && (type != PAPER) && (type != SCISSORS) && (type != BOMB) && (type != FLAG))
	{
		setFileStatus(badPosition, unKnownPiece, numOfRow);
		return false;
	}
	return true;
}

bool FilesPlayer::checkForCorrectJokerType(const char & type, const int & numOfRow)
{
	if ((type != ROCK) && (type != PAPER) && (type != SCISSORS) && (type != BOMB))
	{
		setFileStatus(badPosition, unKnownPieceForJoker, numOfRow);
		return false;
	}
	return true;
}

bool FilesPlayer::checkMoveisLegal(const int & currX, const int & currY, const int & newX, const int & newY)
{
	if ((abs(currX - newX) > 1) || (abs(currY - newY) > 1))
		return true;
	else if (((abs(currX - newX) == 1) && (abs(currY - newY) == 1)) && ((currX != newX) && (currY != newY))) // check for cross
		return true;
	else
		return false;
}

bool FilesPlayer::checkIfPieceCanMove(const char & type, const int & lineNum)
{
	switch (type)
	{
	case BOMB:
		setFileStatus(badMoves, bombCantMove,lineNum);
		return false;
		break;
	case FLAG:
		setFileStatus(badMoves, flagCantMove, lineNum);
		return false;
		break;
	case EMPTY_PIECE:
		setFileStatus(badMoves, notExistPiece, lineNum); //error the player is trying to move a piece that does not exist.
		return false;
		break;
	}
	return true;
}
