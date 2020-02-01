#include <iostream>
#include <vector>

#include "Piece.h"
#include "Board.h"

#include <Windows.h>

using namespace std;

const int WIDTH = 600;
const int HEIGHT = 600;
const int FPS = 60;

sf::RenderWindow window;
sf::Event event;
Board board = Board(window);

int turn;
Piece selectedPiece;

void message(string str) {
	//cout << str << endl;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {

	}
	sf::Text scr = sf::Text(str, font, 50);
	scr.setFillColor(sf::Color::Blue);
    scr.setOrigin((scr.getGlobalBounds().width / 2), 0 * (scr.getGlobalBounds().height / 2));
	scr.setPosition(WIDTH / 2, HEIGHT / 20);

	window.draw(scr);
}

//a method that itterates through selected piece and tests if there are any more moves it can make where it kills the opposite team
bool checkKillingMoves(Board board, Piece piece) {
	Piece p[4][2];
	p[0][0] = board.get(sf::Vector2i((piece.x - 2), (piece.y - 2)));
	p[0][1] = board.get(sf::Vector2i((piece.x - 2 + piece.x) / 2, (piece.y - 2 + piece.y) / 2));
	p[1][0] = board.get(sf::Vector2i((piece.x + 2), (piece.y - 2)));
	p[1][1] = board.get(sf::Vector2i((piece.x + 2 + piece.x) / 2, (piece.y - 2 + piece.y) / 2));
	p[2][0] = board.get(sf::Vector2i((piece.x + 2), (piece.y + 2)));
	p[2][1] = board.get(sf::Vector2i((piece.x + 2 + piece.x) / 2, (piece.y + 2 + piece.y) / 2));
	p[3][0] = board.get(sf::Vector2i((piece.x - 2), (piece.y + 2)));
	p[3][1] = board.get(sf::Vector2i((piece.x - 2 + piece.x) / 2, (piece.y + 2 + piece.y) / 2));
	//test if the piece selected and tg\he piece inbetween qualify taking a piece

	for (int i = 0; i < 4; i++) {
		if (p[i][1].color != piece.color && p[i][0].color != Piece::Color::UNDEFINED && p[i][0].color == Piece::Color::UNDEFINED) {
			return true;
		}
	}
	return false;
}

//the main method for controlling pieces
void move(Piece::Color color) {
	//ui with players
	if (color == Piece::Color::RED) {
		message("Red: Select a Red piece and then click where you want to move.");
	}
	if (color == Piece::Color::BLACK) {
		message("Black: Select a Black piece and then click where you want to move.");
	}

	//if a piece is selected with left mouse test conditions
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		//set the mouse to its actual position
		sf::Vector2i mouse = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);

		//get its coords on the 8x8 board
		if (mouse.x >= 0 && mouse.y >= 0 && mouse.x < window.getSize().x && mouse.y < window.getSize().y) {
			mouse = board.getCoords(mouse);
		}
		else {
			return;
		}

		Piece b = board.get(sf::Vector2i(mouse.x, mouse.y));

		//if the piece is an active square where people can move
		if (mouse.x % 2 == (mouse.y + 1) % 2) {
			//select piece for movement
			if (b.color == color) {
				selectedPiece = Piece(color, mouse.x, mouse.y);
				cout << "Selected Piece at: " << b.x << " " << b.y << endl;
			}

			//normal movement to one piece over
			if ((int) sqrt(pow(mouse.x - selectedPiece.x, 2) + pow(mouse.y - selectedPiece.y, 2)) <= 1 &&
				(int)sqrt(pow(mouse.x - selectedPiece.x, 2) + pow(mouse.y - selectedPiece.y, 2)) > 0) {
				
				//if the space selected is undefined then move piece there and switch turn.
				if (b.color == Piece::Color::UNDEFINED) {
					board.remove(selectedPiece);
					board.place(Piece(color, mouse.x, mouse.y));

					cout << "Placed Piece at: " << mouse.x << " " << mouse.y << endl;

					selectedPiece = Piece();
					turn = (turn + 1) % 2;
				}
				
			}
			//case for taking another piece
			else if ((int)sqrt(pow(mouse.x - selectedPiece.x, 2) + pow(mouse.y - selectedPiece.y, 2)) <= 2 &&
				(int)sqrt(pow(mouse.x - selectedPiece.x, 2) + pow(mouse.y - selectedPiece.y, 2)) > 1 &&
				(mouse.x != selectedPiece.x || mouse.y != selectedPiece.y)) {

				//cout << (mouse.x + selectedPiece.x) / 2 << " " << (mouse.y + selectedPiece.y) << endl;
				//set up the median piece between selected pieces
				Piece p = board.get(sf::Vector2i((mouse.x + selectedPiece.x) / 2, (mouse.y + selectedPiece.y)/2));
				//test if the piece selected and the piece inbetween qualify taking a piece
				cout << p.x << " " << p.y << endl;
				if (p.color != color && p.color != Piece::Color::UNDEFINED && b.color == Piece::Color::UNDEFINED) {
					board.remove(selectedPiece);
					board.place(Piece(color, mouse.x, mouse.y));

					board.remove(p);

					cout << "Placed Piece at: " << mouse.x << " " << mouse.y << endl;

					if (checkLoss) {
						setup();
					}
					else {
						turn = (turn + 1) % 2;
					}
				}
			}
		}
	}
}

//goes by color of piece
bool checkLoss(Piece::Color color) {
	for (int y = 0; y < board.getHeight(); y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			Piece b = board.get(sf::Vector2i(x, y));
			if (b.color == color) {
				return false;
			}
		}
	}
	cout << "game over" << endl;
	return true;
}

void gameManager() {
	if (turn == 0) {
		move(Piece::Color::BLACK);
	} 
	if (turn == 1) {
		move(Piece::Color::RED);
	}
}

void setup() {
	board.printBoard();
	selectedPiece = Piece();
	turn = 0;
}

int main() {
	//ShowWindow(GetConsoleWindow(), SW_RESTORE);

	window.create(sf::VideoMode(WIDTH, HEIGHT), "Checkers");
	window.setFramerateLimit(FPS);

	setup();

	while (window.isOpen()) {
		if (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();

				return 0;
			}
		}

		window.clear();

		gameManager();

		board.draw();
		window.display();
	}

	return 0;
}