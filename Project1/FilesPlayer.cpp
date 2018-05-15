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
			else
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



void FilesPlayer::printError()
{
	switch (error)
	{
	case 1:
		if (status == badPosition)
			cout << "The coordinates in line:" << errLine << " in the input file are not in the range of the board\n";
		else
			cout << "The coordinates in line:" << errLine << " in the move file are not in the range of the board\n";
		break;
	case 2:
		if (status == badPosition)
			cout << "The coordinates inserted in line:" << errLine << " in the input file already have a piece in the board\n";
		else
			cout << "There is a piece in the place that inserted in line:" << errLine << " in the move file\n";
		break;
	case 3:
		cout << "Too many pieces of the same type were inserted in the input file\n";
		break;
	case 4:
		cout << "No flag was inserted in the input file\n";
		break;
	case 5:
		cout << "Unknown piece was inserted in line:" << errLine << " in the input file\n";
		break;
	case 6:
		cout << "Too many rows inserted in the input file \n";
		break;
	case 7:
		cout << "The format of line " << errLine << " in the input file is invalid\n";
		break;
	case 8:
		cout << "The format of line " << errLine << " in the move file is invalid\n";
		break;
	case 9:
		cout << "There is no piece in the place that inserted in line " << errLine << " in the move file\n";
		break;
	case 10:
		cout << "Joker does not exist in the place that inserted in line " << errLine << " in the move file\n";
		break;
	case 11:
		cout << "Joker has changed in line " << errLine << " in the move file into a piece that didn't exist  \n";
		break;
	case 12:
		cout << "The input file is empty\n";
		break;
	case 13:
		cout << "Move a piece in an illegal way in line " << errLine << " in the move file \n";
		break;
	case 14:
		cout << "File doesn't exist";
		break;
	case 15:
		cout << "Unknow piece was inserted for joker in line:" << errLine << " in the input file\n";
		break;
	case 16:
		cout << "The coordinates of the joker in line:" << errLine << " in the move file are not in the range of the board\n";
		break;
	case 17:
		cout << "The bomb in line:" << errLine << " in the move file can't move\n";
		break;
	case 18:
		cout << "The flag in line:" << errLine << " in the move file can't move\n";
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

void FilesPlayer::createOutputFile(Player ** p,int winner)
{
	ofstream outfile("output.txt");
	if (outfile.is_open())
	{
		outfile << "Winner: " << winner << "\n";
		outfile << "Reason: " ;
		if (winner == 1)
		{
			outfile << p[1]->returnReason();
			if (p[1]->getStatus()>2)
				outfile  <<"for player 2 ";
			if (((FilesPlayer*)p[1])->errLine!=0)
			{
				outfile << "line " << ((FilesPlayer*)p[1])->errLine;
			}
		}
		else if (winner == 2)
		{
			outfile << p[0]->returnReason();
			if (p[0]->getStatus()>2)
				outfile << "for player 1 ";
			if (((FilesPlayer*)p[0])->errLine!=0)
			{
				outfile << "line " << ((FilesPlayer*)p[0])->errLine;
			}
		}
		else if (winner == 0)
		{
			if (p[0]->getStatus() == p[1]->getStatus())
			{
				if (p[0]->getStatus() ==badPosition)
					outfile << "Bad Positioning input files for both players- player 1: line " << ((FilesPlayer*)p[0]) << ", player 2: line " << ((FilesPlayer*)p[1]);
				if ((p[0]->getStatus() == moveFilesDone) || (p[0]->getStatus() ==flagsCaptured) || (p[0]->getStatus() ==allEaten))
					outfile << "A tie - both Moves input files done without a winner";
			}
			else
			{
				outfile << p[0]->returnReason();
				if (((FilesPlayer*)p[0])->errLine != 0)
				{
					outfile << " player 1 line " << ((FilesPlayer*)p[0]);
				}
				outfile << " and "<< p[1]->returnReason();
				if (((FilesPlayer*)p[0]) != 0)
				{
					outfile << " player 2 line " << ((FilesPlayer*)p[0]);
				}
			}
		}
		outfile << "\n\n";
		if ((p[0]->getStatus() != badPosition) && (p[1]->getStatus() != badPosition))
		{
			drawBoardToFile(outfile,p);
		}
		outfile.close();
	}
	else {
		gotoxy(1, 28);
		cout << "can't Create ouput file";

	}
}

void FilesPlayer::drawBoardToFile(ofstream & outfile, Player ** p)
{
	for (int j = 1; j < 11; j++)
	{
		outfile << "|";
		for (int i = 1; i < 11; i++)
		{
			if (((FilesPlayer*)p[0])->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			{
				if (((FilesPlayer*)p[0])->playerBoard[i][j].getPieceJoker())
					outfile << " " << 'j' << "  |";
				else
					outfile << " " << (char)(((FilesPlayer*)p[0])->playerBoard[i][j].getPieceType() + 32) << "  |";
			}
			else if (((FilesPlayer*)p[1])->playerBoard[i][j].getPieceType() != EMPTY_PIECE)
			{
				if (((FilesPlayer*)p[1])->playerBoard[i][j].getPieceJoker())
					outfile << " " << JOKER << "  |";
				else
					outfile << " " << ((FilesPlayer*)p[1])->playerBoard[i][j].getPieceType() << "  |";
			}
			else
				outfile << "    |";
		}
		outfile << "\n";
	}
}



