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
	errorLine = 0;
}

Player::~Player()
{
	for (int i = 0; i < M + 1; i++) {
		delete[] playerBoard[i];
	}
	delete[] playerBoard;
}


bool Player::move(int moveNum, int& newXLocation, int& newYLocation, int& oldXLocation, int& oldYLocation, int& jokerXLocation, int& jokerYLocation, char& newJokerType)
{
	if (moveFile.readMove(moveNum, newXLocation, newYLocation, oldXLocation, oldYLocation, jokerXLocation, jokerYLocation, newJokerType, playerBoard))
	{
		return true;
	}
	else
	{
		setPlayerStatus(moveFile);
		return false;
	}
	//This functino reads the move files and check for erros.

}


void Player::setPlayerStatus(Reason reason, Error theError, int line) //If error was found in one of the files this functino changes the relevant player status.
{
	status = reason;
	error = theError;
	errorLine = line;
}

void Player::setPlayerStatus(const FilesPlayer& currFile)
{
	status = currFile.getFileStatus();
	errorLine = currFile.getErrorLine();
	error = currFile.getFileError();
}

void Player::readFromFile()//This function reads the first file and checks for errors in
{
	startFile.setInputFile(startGameFile,playerBoard);
	bool illegalFile = false;
	int numOfRows = 0, inputIndex = 0;
	string tmpRead[10] = { "0" };
	string getInput;
	int index=0;
	ifstream inFile(this->startGameFile);
	int xLocation, yLocation;
	char type;
	int maxRows = startFile.getnumOfStartMoves();
	if (startFile.getFileStatus() != noReason)
	{
		setPlayerStatus(startFile);
	}
	while (numOfRows < maxRows)
	{
		index = 0;
		getInput = startFile.getCurrLine("inputFile", numOfRows);
		stringstream chs(getInput);
		string omer;
		while (getline(chs, omer, ' '))
			tmpRead[index++] = omer;
		index = 0;
		numOfRows++;
		type = tmpRead[index++][0];
		xLocation = stoi(tmpRead[index++]);
		yLocation = stoi(tmpRead[index++]);
		if (type == JOKER)
		{
			playerBoard[xLocation][yLocation].setPieceJoker(true);
			countPieces(JOKER);
			type = tmpRead[index++][0];
			playerBoard[xLocation][yLocation].setPieceType(type);
		}
		else 
		{
			playerBoard[xLocation][yLocation].setPieceType(type);
			countPieces(type);
		}
	}
}
void Player::checkValidityiPieces()
{
	//The print is just for checking how many pieces each type there is for the each player
	//cout << "CounterPieces P:" << counterPieces[P] << " R:" << counterPieces[R] << " B:" << counterPieces[B] << " S:" << counterPieces[S] << " F:" << counterPieces[F] << " J:" << counterPieces[J] << "\n";
	if (counterPieces[P] > NUM_OF_PAPER || counterPieces[R] > NUM_OF_ROCK || counterPieces[B] > NUM_OF_BOMB || counterPieces[J] > NUM_OF_JOKER ||
		counterPieces[S] > NUM_OF_SCISSORS || counterPieces[F] > NUM_OF_FLAG)
	{
		setPlayerStatus(badPosition, tooManyPieces, 0); //-	A PIECE type appears in file more than its number
	}
	if (counterPieces[F] < 1)
	{
		setPlayerStatus(badPosition, noFlag, 0); // Missing flag
	}
}

void Player::removePiece(int i, int j)
{
	char type = playerBoard[i][j].getPieceType();
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


void Player::printError()
{
	switch (error)
	{
	case 1:
		if (status == badPosition)
			cout << "The coordinates in line:" << errorLine << " in the input file are not in the range of the board\n";
		else
			cout << "The coordinates in line:" << errorLine << " in the move file are not in the range of the board\n";
		break;
	case 2:
		if (status == badPosition)
			cout << "The coordinates inserted in line:" << errorLine << " in the input file already have a piece in the board\n";
		else
			cout << "There is a piece in the place that inserted in line:" << errorLine << " in the move file\n";
		break;
	case 3:
		cout << "Too many pieces of the same type were inserted in the input file\n";
		break;
	case 4:
		cout << "No flag was inserted in the input file\n";
		break;
	case 5:
		cout << "Unknown piece was inserted in line:" << errorLine << " in the input file\n";
		break;
	case 6:
		cout << "Too many rows inserted in the input file \n";
		break;
	case 7:
		cout << "The format of line " << errorLine << " in the input file is invalid\n";
		break;
	case 8:
		cout << "The format of line " << errorLine << " in the move file is invalid\n";
		break;
	case 9:
		cout << "There is no piece in the place that inserted in line " << errorLine << " in the move file\n";
		break;
	case 10:
		cout << "Joker does not exist in the place that inserted in line " << errorLine << " in the move file\n";
		break;
	case 11:
		cout << "Joker has changed in line " << errorLine << " in the move file into a piece that didn't exist  \n";
		break;
	case 12:
		cout << "The input file is empty\n";
		break;
	case 13:
		cout << "Move a piece in an illegal way in line " << errorLine << " in the move file \n";
		break;
	case 14:
		cout << "File doesn't exist";
		break;
	case 15:
		cout << "Unknow piece was inserted for joker in line:" << errorLine << " in the input file\n";
		break;
	case 16:
		cout << "The coordinates of the joker in line:" << errorLine << " in the move file are not in the range of the board\n";
		break;
	case 17:
		cout << "The bomb in line:" << errorLine << " in the move file can't move\n";
		break;
	case 18:
		cout << "The flag in line:" << errorLine << " in the move file can't move\n";
		break;
	case 19:
		if (status == badPosition)
			cout << "There is an error opening the input file \n";
		else
			cout << "There is an error opening the move file \n";
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
