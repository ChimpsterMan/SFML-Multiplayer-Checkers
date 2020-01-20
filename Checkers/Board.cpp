#include <iostream>
#include "SFML/Graphics.hpp"
#include "Piece.h"
#include "Board.h"

using namespace std;

Board::Board(sf::RenderWindow& w):window(&w)
{

	//make all the slots for the width and height of board
	for (int y = 0; y < HEIGHT; y++) {
		vector<Piece> v;
		board.push_back(v);
		for (int x = 0; x < WIDTH; x++) {
			Piece p = Piece();
			board[y].push_back(p);
		}
	}

	//set board for first game
	Board::reset();
}

void Board::place(Piece piece) {
	board[piece.y][piece.x] = piece;
}

void Board::remove(Piece piece) {
	board[piece.y][piece.x] = Piece();
}

void Board::reset() {
	//empty

	//black
	for (int y = 1; y <= 3; y++) {
		for (int x = y % 2; x < WIDTH; x += 2) {
			board[y - 1][x] = Piece(Piece::Color::BLACK, x, y - 1);
		}
	}

	//red
	for (int y = HEIGHT - 2; y <= HEIGHT; y++) {
		for (int x = y % 2; x < WIDTH; x += 2) {
			board[y - 1][x] = Piece(Piece::Color::RED, x, y - 1);
		}
	}
}

void Board::printBoard() {
	cout << "Board: " << endl;
	for (int x = 0; x <= WIDTH*2; x++) {
		cout << '#';
	}
	cout << endl;
	for (int y = 0; y < HEIGHT; y++) {
		cout << '#';
		for (int x = 0; x < WIDTH - 1; x++) {
			board[y][x].print();
			cout << ' ';
		}
		board[y][WIDTH - 1].print();
		cout << '#' << endl;
	}
	for (int x = 0; x <= WIDTH*2; x++) {
		cout << '#';
	}
	cout << endl;
}

void Board::draw()
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(window->getSize().x / WIDTH, window->getSize().y / HEIGHT));
			if (x % 2 == (y) % 2) {
				rect.setFillColor(sf::Color(82, 99, 99));
			}
			else if (x % 2 == (y + 1) % 2) {
				rect.setFillColor(sf::Color(115, 63, 0));
			}
			rect.setPosition(sf::Vector2f(x * window->getSize().x / WIDTH, (y)*window->getSize().y / HEIGHT));
			window->draw(rect);
		}
	}

	//draw pieces
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			if (board[y][x].color != Piece::Color::UNDEFINED) {
				sf::CircleShape circ = sf::CircleShape(window->getSize().x / WIDTH / 2);
				if (board[y][x].color == Piece::Color::BLACK) {
					circ.setFillColor(sf::Color::Black);
				}
				if (board[y][x].color == Piece::Color::RED) {
					circ.setFillColor(sf::Color::Red);
				}

				circ.setPosition(sf::Vector2f((x) * window->getSize().x / WIDTH, (y) * window->getSize().y / HEIGHT));
				window->draw(circ);
			}
		}
	}
}

sf::Vector2i Board::getCoords(sf::Vector2i coords) {
	sf::Vector2i newCoords = sf::Vector2i(coords.x / (window->getSize().x / WIDTH), coords.y / (window->getSize().y / HEIGHT));
	return newCoords;
}

Piece Board::get(sf::Vector2i position) {
	return board[position.y][position.x];
}

int Board::getWidth() {
	return Board::WIDTH;
}

int Board::getHeight() {
	return Board::WIDTH;
}