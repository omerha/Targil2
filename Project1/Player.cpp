#include "Player.h"

using namespace std;


Player::Player() //Constructor
{
	status = noReason;
	for (int i = 0; i < 6; i++)
		counterPieces[i] = 0;
	playerBoard = new Piece*[N + 1];
	for (int i = 0; i < M + 1; i++) {
		playerBoard[i] = new Piece[M + 1];
	}
	error = noError;
}

Player::~Player()
{
	for (int i = 0; i < M + 1; i++) {
		delete[] playerBoard[i];
	}
	delete[] playerBoard;
}





void Player::setPlayerStatus(Reason reason, Error theError) //If error was found in one of the files this functino changes the relevant player status.
{
	status = reason;
	error = theError;
}




void Player::checkValidityiPieces()
{
	//The print is just for checking how many pieces each type there is for the each player
	//cout << "CounterPieces P:" << counterPieces[P] << " R:" << counterPieces[R] << " B:" << counterPieces[B] << " S:" << counterPieces[S] << " F:" << counterPieces[F] << " J:" << counterPieces[J] << "\n";
	if (counterPieces[P] > NUM_OF_PAPER || counterPieces[R] > NUM_OF_ROCK || counterPieces[B] > NUM_OF_BOMB || counterPieces[J] > NUM_OF_JOKER ||
		counterPieces[S] > NUM_OF_SCISSORS || counterPieces[F] > NUM_OF_FLAG)
	{
		setPlayerStatus(badPosition, tooManyPieces); //-	A PIECE type appears in file more than its number
	}
	if (counterPieces[F] < 1)
	{
		setPlayerStatus(badPosition, noFlag); // Missing flag
	}
}

void Player::removePiece(int i, int j)
{
	char type = playerBoard[i][j].getPieceType();
	playerBoard[i][j].setPieceJoker(false);
	playerBoard[i][j].setPieceType(EMPTY_PIECE);
	if (playerBoard[i][j].getPieceJoker())
	{
		counterPieces[J]--;
		return;
	}
	else
	{
		switch (type)
		{
		case ROCK:
			counterPieces[R]--;
			break;
		case SCISSORS:
			counterPieces[S]--;
			break;
		case PAPER:
			counterPieces[P]--;
			break;
		case BOMB:
			counterPieces[B]--;
			break;
		case FLAG:
			counterPieces[F]--;
			break;
		}
	}
}
void Player::countPieces(char type)
{
	switch (type)
	{
	case ROCK:
		counterPieces[R] += 1;
		break;
	case PAPER:
		counterPieces[P] += 1;
		break;
	case BOMB:
		counterPieces[B] += 1;
		break;
	case JOKER:
		counterPieces[J] += 1;
		break;
	case FLAG:
		counterPieces[F] += 1;
		break;
	case SCISSORS:
		counterPieces[S] += 1;
		break;
	}

}




string Player::returnReason()
{
	switch (status)
	{
	case noReason:
		return "No reason";
		break;
	case flagsCaptured:
		return "All flags of the opponent are captured";
		break;
	case allEaten:
		return "All moving PIECEs of the opponent are eaten";
		break;
	case badPosition:
		return "Bad Positioning input file ";
		break;
	case badMoves:
		return "Bad Moves input file ";
		break;
	default:
		return "No reason ";
		break;
	}
}

void Player::hideJoker()
{
	int counterJoker = 0;
	for (int i = 1; i <= N && counterJoker < counterPieces[J]; i++)
	{
		for (int j = 1; j <= M && counterJoker < counterPieces[J]; j++)
		{
			if (playerBoard[i][j].getPieceJoker())
			{
				playerBoard[i][j].setRevealJokerStatus(false);
				counterJoker++;
			}
		}
	}
}
bool Player::checkForCorrectJokerType(const char & type)
{
	if ((type != ROCK) && (type != PAPER) && (type != SCISSORS) && (type != BOMB))
		return false;
	
	return true;
}

bool Player::checkMoveisLegal(const int & currX, const int & currY, const int & newX, const int & newY)
{
	if ((abs(currX - newX) > 1) || (abs(currY - newY) > 1))
		return true;
	else if (((abs(currX - newX) == 1) && (abs(currY - newY) == 1)) && ((currX != newX) && (currY != newY))) // check for cross
		return true;
	else
		return false;
}

bool Player::checkXYInRange(int num, char cord)
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

Error Player::checkIfPieceCanMove(const char & type)
{
	switch (type)
	{
	case BOMB:
		return bombCantMove;
		break;
	case FLAG:
		return flagCantMove;
		break;
	case EMPTY_PIECE:
		return notExistPiece;
		break;
	}
	return noError;
}

bool Player::checkForCorrectType(const char& type)
{
	if ((type != ROCK) && (type != PAPER) && (type != SCISSORS) && (type != BOMB) && (type != FLAG))
	{

		return false;
	}
	return true;
}



Error Player::validateMove(int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation)
{
	if (playerBoard[newXLocation][newYLocation].getPieceType() != EMPTY_PIECE)
	{
		return sameLocation;
	}
	if (!(checkXYInRange(oldXLocation, 'X') && checkXYInRange(newXLocation, 'X') && checkXYInRange(newYLocation, 'Y') && checkXYInRange(oldYLocation, 'Y')))
	{
		return notInRange;
	}
	if (checkMoveisLegal(oldXLocation, oldYLocation, newXLocation, newYLocation)) // move more than on square
	{
		return moveIllegal;
	}
	Error temp = Player::checkIfPieceCanMove(playerBoard[oldXLocation][oldYLocation].getPieceType());
	if (temp != noError)
	{
		return temp;
	}
}
string* Player::parseLine(string line, int & size, Error err)
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
				{
					status = badPosition;
					error = err;
					return nullptr;
				}
			}
			else if (getInput[i].empty())
			{
				status = badPosition;
				error = err;
				return nullptr;
			}
			out[i] = getInput[i];
		}
		size = inputIndex;
		return out;
	}
	else
		return nullptr;
}
bool Player::readCurrentStartLine(string currentLine, Error err,int& lenLine)
{
	string tmpRead;
	string* getInput = nullptr;
	int inputIndex = 0;
	char type;
	int xLocation, yLocation, index = 0;
	getInput = parseLine(currentLine, inputIndex, err);
	if (status != noReason)
	{
		return false;
	}
	if ((inputIndex == 3) || (inputIndex == 4))
	{
		type = getInput[index][index];
		if (islower(type))
			type = toupper(type);
		if (isdigit(getInput[1][0]) && isdigit(getInput[2][0]))
		{
			xLocation = stoi(getInput[++index]);
			yLocation = stoi(getInput[++index]);
		}
		else
		{
			setPlayerStatus(badPosition, err);
			return false;
		}
		if (!(checkXYInRange(yLocation, 'Y') && checkXYInRange(xLocation, 'X')))
		{
			setPlayerStatus(badPosition, notInRange);
			return false;
		}
		if (playerBoard[xLocation][yLocation].getPieceType() != EMPTY_PIECE)// There is a piece in this location
		{
			setPlayerStatus(badPosition, sameLocation);
			return false;
		}
	}
	else
	{
		if (inputIndex) {
			setPlayerStatus(badPosition,err); // the length line isn't 3 or 4 chars
			return false;
		}
	}
	if (inputIndex == 4)
	{
		if (type == JOKER)
		{
			type = getInput[++index][0];
			if (islower(type))
				type = toupper(type);
			if (!(checkForCorrectJokerType(type)))
			{
				setPlayerStatus(badPosition, unKnownPieceForJoker);
				return false;
			}
			playerBoard[xLocation][yLocation].setPieceJoker(true);
			countPieces(JOKER);
			playerBoard[xLocation][yLocation].setPieceType(type);
			return true;
		}
		else
		{
			setPlayerStatus(badPosition, err);
			return false;
		}
	}
	else if (inputIndex == 3)
	{
		if (!(checkForCorrectType(type)))
		{
			setPlayerStatus(badPosition, unKnownPiece);
			return false;
		}
	}
	playerBoard[xLocation][yLocation].setPieceType(type);
	countPieces(type);
	return true;
}
bool Player::readCurrentMove(string currentLine, Error err, int & newXLocation, int & newYLocation, int & oldXLocation, int & oldYLocation, int & jokerXLocation, int & jokerYLocation, char & newJokerType)
{
	int xJoker, yJoker;
	string* currInput = nullptr;
	int numOfIndex = 0;
	char nJokerType;
	int currX = 0, currY = 0, newX = 0, newY = 0;
	Error checkMovesError;
	currInput = parseLine(currentLine, numOfIndex, err);
	if (status != noReason)
	{
		return false;
	}
	if (numOfIndex < 4 || numOfIndex>8)
	{
		setPlayerStatus(badMoves, err); //error - too many or too few arguments in line.
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
		setPlayerStatus(badMoves, err);
		return false;
	}
	checkMovesError = validateMove(newX, newY, currX, currY);
	if (checkMovesError != noError)
	{
		setPlayerStatus(badMoves, checkMovesError);
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
					setPlayerStatus(badMoves, wrongInputJoker);
					return false;
				}
				nJokerType = currInput[7][0];
				if (islower(nJokerType))
					nJokerType = toupper(nJokerType);
				if (!(checkXYInRange(xJoker, 'X') && checkXYInRange(yJoker, 'Y')))//Something is wrong with joker xy coordinates
				{
					setPlayerStatus(badMoves, jokerNotInRange);
					return false;
				}
				else if (playerBoard[xJoker][yJoker].getPieceJoker() || (playerBoard[currX][currY].getPieceJoker() && xJoker == newX && yJoker == newY))
				{
					if (!(checkForCorrectJokerType(nJokerType)))
					{
						return false;
						setPlayerStatus(badPosition, unKnownPieceForJoker);
					}
					else
					{
						jokerXLocation = xJoker;
						jokerYLocation = yJoker;
						newJokerType = nJokerType;
					}
				}
				else
				{
					setPlayerStatus(badMoves, notExistJoker); //Error- not exit joker in this location
					return false;
				}
			}
			else //The wrong is for example: "K:" insted of "J:"
			{
				setPlayerStatus(badMoves, err);
				return false;
			}
		}
		else //The wrong, for example: "J::" insted of "J:"
		{
			setPlayerStatus(badMoves,err);
			return false;
		}
	}
	delete[] currInput;
	playerBoard[newX][newY].setRevealType(playerBoard[currX][currY].getRevealType());
	playerBoard[newX][newY].setPieceType(playerBoard[currX][currY].getPieceType());
	playerBoard[currX][currY].setPieceType(EMPTY_PIECE);
	oldXLocation = currX;
	oldYLocation = currY;
	newXLocation = newX;
	newYLocation = newY;
	return true;
}