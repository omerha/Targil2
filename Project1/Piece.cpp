#include "Piece.h"


void Piece::drawPiece(int xL, int yL)
{
	gotoxy(xL*3+3, yL*2+3);
	cout << pieceType;
}

void Piece::removePiece(int xL, int yL)
{
	setTextRemoveColor(BLACK);
	gotoxy(xL * 3+3, yL * 2+3);
	cout << " ";
	revealJoker = false;
	revealType = false;
	setTextRemoveColor(WHITE);
}

void Piece::drawPiece(Color color, int xL, int yL)
{
	if (joker)
	{
		if (revealJoker)
			setTextbBackground(color);
	revealJoker = true;
	}
	else
		setTextColor(color);
	gotoxy(xL * 3+3, yL * 2+3);
	cout << pieceType;
	//revealType = true;
}

void Piece::drawUnknownPiece(Color color, int xL, int yL)
{
	setTextColor(color);
	gotoxy(xL * 3+3, yL * 2+3);
	if (revealType)
		cout << pieceType;
	else
		cout << UNKNOWN_PIECE;
}

bool Piece::operator>(const Piece & p) 
{ //The operator> function returns TRUE if the active object is stronger than the paramater object, and FALSE if the active object is weaker.
	switch (pieceType)
	{
		case ROCK:
			if (p.pieceType == SCISSORS) //The active object is stornger
			{
				return true;
			}
			else if (p.pieceType == PAPER) //The active object is weaker
			{
				return false;
			}
			break;
		case SCISSORS:
			if (p.pieceType == ROCK) //The active object is weaker
			{
				return false;
			}
			else if (p.pieceType == PAPER) //The active object is stornger
			{
				return true;
			}
			break;
		case PAPER:
			if (p.pieceType == SCISSORS) //The active object is weaker
			{
				return false;
			}
			else if (p.pieceType == ROCK) //The active object is stornger
			{
				return true;
			}
			break;
		default:
			return false;
			break;
	}
	

	return false;
}

bool Piece::operator==(const Piece & p) 
{ //The operator= function returns TRUE if the active object is equal to the paramater object, and FALSE if not.
	//In case that there is a bomb to the active object or the parameter object the function returns TRUE because the two  pieces are lose in this situation.
	//In case that there is a flag to the active object or the parameter object the function returns TRUE because the two  pieces are lose in this situation.
	if (pieceType == p.pieceType)
		return true;
	else if ((pieceType == BOMB) || (p.pieceType == BOMB))
		return true;
	else if ((joker == true) || (p.joker==true))
		return true;
	return false;
}





