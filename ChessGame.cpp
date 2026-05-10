#include "stdafx.h"
#include "piece.h"
#include "board.h"
#include <SFML/Graphics.hpp>
#include <string>

int tileSize = 80;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 700), "Chess Game - NUCES");

	// Load textures
	std::string names[12] = {
		"wK","wQ","wR","wB","wN","wP",
		"bK","bQ","bR","bB","bN","bP"
	};
	sf::Texture textures[12];
	for (int i = 0; i < 12; i++)
	{
		sf::Image image;
		image.loadFromFile("pieces/" + names[i] + ".png");
		image.createMaskFromColor(sf::Color::White);
		textures[i].loadFromImage(image);
		textures[i].setSmooth(true);
	}

	// Font
	sf::Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	// Status text
	sf::Text statusText;
	statusText.setFont(font);
	statusText.setCharacterSize(22);
	statusText.setPosition(10, 650);

	// Check warning text
	sf::Text checkText;
	checkText.setFont(font);
	checkText.setCharacterSize(26);
	checkText.setFillColor(sf::Color::Red);
	checkText.setStyle(sf::Text::Bold);
	checkText.setPosition(200, 650);

	Board board;
	int selectedRow = -1, selectedCol = -1;
	bool pieceSelected = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (!board.isGameOver() &&
				event.type == sf::Event::MouseButtonPressed)
			{
				int col = event.mouseButton.x / tileSize;
				int row = event.mouseButton.y / tileSize;

				if (row < 0 || row > 7 || col < 0 || col > 7) continue;

				if (!pieceSelected)
				{
					Piece* p = board.getPiece(row, col);
					if (p != nullptr && p->getColor() == board.getTurn())
					{
						selectedRow = row;
						selectedCol = col;
						pieceSelected = true;
					}
				}
				else
				{
					bool moved = board.movePiece(
						selectedRow, selectedCol, row, col);
					pieceSelected = false;
					selectedRow = -1;
					selectedCol = -1;
				}
			}
		}

		window.clear(sf::Color(30, 30, 30));

		// Draw board
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				// Draw tile
				sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
				tile.setPosition(c * tileSize, r * tileSize);

				if (pieceSelected && r == selectedRow && c == selectedCol)
					tile.setFillColor(sf::Color(100, 200, 100));
				else if ((r + c) % 2 == 0)
					tile.setFillColor(sf::Color(240, 217, 181));
				else
					tile.setFillColor(sf::Color(181, 136, 99));

				window.draw(tile);

				// Draw piece
				Piece* p = board.getPiece(r, c);
				if (p != nullptr)
				{
					std::string symbol = p->getSymbol();
					for (int i = 0; i < 12; i++)
					{
						if (names[i] == symbol)
						{
							sf::Sprite sprite(textures[i]);
							sprite.setScale(
								(float)tileSize / textures[i].getSize().x,
								(float)tileSize / textures[i].getSize().y
							);
							sprite.setPosition(c * tileSize, r * tileSize);
							window.draw(sprite);
						}
					}
				}
			}
		}

		// ===== STATUS BAR =====
		if (board.isGameOver())
		{
			if (board.isStalemate())
			{
				statusText.setString("STALEMATE! It's a Draw!");
				statusText.setFillColor(sf::Color::Yellow);
			}
			else
			{
				std::string w = (board.getWinner() == 'w') ?
					"White" : "Black";
				statusText.setString(w + " wins! CHECKMATE!");
				statusText.setFillColor(sf::Color::Green);
			}
			checkText.setString("");
		}
		else
		{
			std::string turn = (board.getTurn() == 'w') ?
				"White's Turn" : "Black's Turn";
			statusText.setString(turn);
			statusText.setFillColor(
				board.getTurn() == 'w' ?
				sf::Color::White : sf::Color(180, 180, 180));

			// Show CHECK warning
			if (board.isInCheck())
				checkText.setString("  CHECK!");
			else
				checkText.setString("");
		}

		window.draw(statusText);
		window.draw(checkText);
		window.display();
	}
	system("pause");
	return 0;
}