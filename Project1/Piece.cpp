#include "Piece.h"


void Piece::drawPiece(int xL, int yL)
{
	gotoxy(xL*3+3, yL*2+3);
	cout << *this;
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
		setTextbBackground(color);
	revealJoker = true;
	}
	else
		setTextColor(color);
	gotoxy(xL * 3+3, yL * 2+3);
	cout << *this;

}

void Piece::drawUnknownPiece(Color color, int xL, int yL)
{
	setTextColor(color);
	gotoxy(xL * 3+3, yL * 2+3);
	if (revealType)
		cout << *this;
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
	else if ((pieceType == FLAG) || (p.pieceType == FLAG))
		return true;
	else if ((pieceType == BOMB) || (p.pieceType == BOMB))
		return true;
	return false;
}

bool Piece::operator<(const Piece & p)
{
	return (!(*this > p));
}

const Piece & Piece::operator=(const Piece & p)
{
	if (this != &p)
	{
		pieceType = p.pieceType;
		joker = p.joker;
		revealType = p.revealType;
		revealJoker = p.revealJoker;
	}
	return *this;
}

ostream & operator<<(ostream & out, const Piece & p)
{
	out << p.pieceType;
	return out;
}
