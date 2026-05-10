#pragma once
#include "piece.h"

class Board
{
private:
	Piece* grid[8][8];
	char currentTurn;
	bool gameOver;
	char winner;
	bool inCheckState;
	bool stalemateState;

public:
	Board()
	{
		currentTurn = 'w';
		gameOver = false;
		winner = ' ';
		inCheckState = false;
		stalemateState = false;

		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				grid[r][c] = nullptr;

		setupBoard();
	}

	~Board()
	{
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (grid[r][c] != nullptr)
					delete grid[r][c];
	}

	void setupBoard()
	{
		// Black pieces
		grid[0][0] = new Rook('b', 0, 0);
		grid[0][1] = new Knight('b', 0, 1);
		grid[0][2] = new Bishop('b', 0, 2);
		grid[0][3] = new Queen('b', 0, 3);
		grid[0][4] = new King('b', 0, 4);
		grid[0][5] = new Bishop('b', 0, 5);
		grid[0][6] = new Knight('b', 0, 6);
		grid[0][7] = new Rook('b', 0, 7);
		for (int c = 0; c < 8; c++)
			grid[1][c] = new Pawn('b', 1, c);

		// White pieces
		grid[7][0] = new Rook('w', 7, 0);
		grid[7][1] = new Knight('w', 7, 1);
		grid[7][2] = new Bishop('w', 7, 2);
		grid[7][3] = new Queen('w', 7, 3);
		grid[7][4] = new King('w', 7, 4);
		grid[7][5] = new Bishop('w', 7, 5);
		grid[7][6] = new Knight('w', 7, 6);
		grid[7][7] = new Rook('w', 7, 7);
		for (int c = 0; c < 8; c++)
			grid[6][c] = new Pawn('w', 6, c);
	}
};