#pragma once
#include <string>

//  BASE CLASS 
class Piece
{
protected:
	char color; // 'w' or 'b'
	char type;  // 'K','Q','R','B','N','P'
	int row, col;

public:
	Piece(char color, char type, int row, int col)
		: color(color), type(type), row(row), col(col) {}

	virtual ~Piece() {}

	// Getters
	char getColor() const { return color; }
	char getType()  const { return type; }
	int  getRow()   const { return row; }
	int  getCol()   const { return col; }

	// Setters
	void setPosition(int r, int c) { row = r; col = c; }

	// Pure virtual
	virtual bool isValidMove(int toRow, int toCol, Piece* board[8][8]) const = 0;

	virtual std::string getSymbol() const
	{
		std::string s = "";
		s += color;
		s += type;
		return s;
	}

protected:
	bool inBounds(int r, int c) const
	{
		return r >= 0 && r < 8 && c >= 0 && c < 8;
	}

	bool isPathClear(int toRow, int toCol,
		Piece* board[8][8]) const
	{
		int stepR = (toRow == row) ? 0 : (toRow > row ? 1 : -1);
		int stepC = (toCol == col) ? 0 : (toCol > col ? 1 : -1);
		int r = row + stepR;
		int c = col + stepC;
		while (r != toRow || c != toCol)
		{
			if (board[r][c] != nullptr) return false;
			r += stepR;
			c += stepC;
		}
		return true;
	}
};
