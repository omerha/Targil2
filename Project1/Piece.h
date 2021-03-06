#pragma once
using namespace std;
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "io_utils.h"
#include "Color.h"

#define EMPTY_PIECE '-'
#define BOMB 'B'
#define JOKER 'J'
#define SCISSORS 'S'
#define ROCK 'R'
#define FLAG 'F'
#define PAPER 'P'
#define UNKNOWN_PIECE "U"
#define NUM_OF_PIECES_TYPE 6

enum Pieces
{
	R = 0,
	P = 1,
	S = 2,
	J = 3,
	B = 4,
	F = 5
};


class Piece
{
	char pieceType;
	bool joker;
	bool revealType;
	bool revealJoker;
public: 

	Piece()
	{
		revealJoker = true;
		revealType = false;
		joker = false;
		pieceType = EMPTY_PIECE;
	}
	char getPieceType()
	{
		return pieceType;
	}
	bool getPieceJoker()
	{
		return joker;
	}
	void setRevealJokerStatus(bool jokerStatus)
	{
		revealJoker = jokerStatus;
	}
	void setPieceType(char pPieceType)
	{
		pieceType = pPieceType;
	}
	void setPieceJoker(bool pJoker)
	{
		joker = pJoker;
	}
	bool getPieceJokerRevealStatus()
	{
		return revealJoker;
	}
	void setRevealType(bool nRevealType)
	{
		revealType = nRevealType;
	}
	bool getRevealType()
	{
		return revealType;
	}

	void drawPiece(int xL,int yL);
	void removePiece(int xL, int yL);
	void drawPiece(Color color, int xL, int yL);
	void drawUnknownPiece(Color color, int xL, int yL);
	bool operator > (const Piece &p) ;
	bool operator == (const Piece &p) ;
	bool operator < (const Piece &p);
	friend ostream& operator<< (ostream& out, const Piece& p);
	const Piece& operator = (const Piece & p);
};