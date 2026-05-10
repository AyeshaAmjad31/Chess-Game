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
	// Getters
	Piece* getPiece(int r, int c) const { return grid[r][c]; }
	char getTurn()        const { return currentTurn; }
	bool isGameOver()     const { return gameOver; }
	char getWinner()      const { return winner; }
	bool isInCheck()      const { return inCheckState; }
	bool isStalemate()    const { return stalemateState; }

	// ===== CHECK DETECTION =====
	// Find king position of given color
	void findKing(char color, int& kr, int& kc) const
	{
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (grid[r][c] != nullptr &&
					grid[r][c]->getColor() == color &&
					grid[r][c]->getType() == 'K')
				{
					kr = r; kc = c;
					return;
				}
	}

	// Is the given color's king in check?
	bool isKingInCheck(char color, Piece* tempGrid[8][8]) const
	{
		int kr = -1, kc = -1;
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (tempGrid[r][c] != nullptr &&
					tempGrid[r][c]->getColor() == color &&
					tempGrid[r][c]->getType() == 'K')
				{
					kr = r; kc = c;
				}

		if (kr == -1) return false;

		// Check if any opponent piece can attack the king
		char opponent = (color == 'w') ? 'b' : 'w';
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				if (tempGrid[r][c] != nullptr &&
					tempGrid[r][c]->getColor() == opponent)
					if (tempGrid[r][c]->isValidMove(kr, kc, tempGrid))
						return true;

		return false;
	}

	// Simulate a move and check if it leaves king in check
	bool moveLeavesKingInCheck(int fr, int fc, int tr, int tc) const
	{
		// Copy grid
		Piece* tempGrid[8][8];
		for (int r = 0; r < 8; r++)
			for (int c = 0; c < 8; c++)
				tempGrid[r][c] = grid[r][c];

		// Simulate move
		tempGrid[tr][tc] = tempGrid[fr][fc];
		tempGrid[fr][fc] = nullptr;

		char color = tempGrid[tr][tc]->getColor();
		return isKingInCheck(color, tempGrid);
	}

	// Does the current player have any valid moves?
	bool hasValidMoves(char color)
	{
		for (int fr = 0; fr < 8; fr++)
			for (int fc = 0; fc < 8; fc++)
			{
				if (grid[fr][fc] == nullptr) continue;
				if (grid[fr][fc]->getColor() != color) continue;

				for (int tr = 0; tr < 8; tr++)
					for (int tc = 0; tc < 8; tc++)
					{
						if (grid[fr][fc]->isValidMove(tr, tc, grid))
							if (!moveLeavesKingInCheck(fr, fc, tr, tc))
								return true;
					}
			}
		return false;
	}
};