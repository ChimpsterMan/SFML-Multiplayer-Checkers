#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
//#include "Piece.h"

using namespace std;

class Board {
private:
	const int WIDTH = 8;
	const int HEIGHT = 8;
	vector<vector<Piece>> board;
	//a pointer to the window instance so you can draw from both the main class and the board class
	sf::RenderWindow *window;

public:
	Board(sf::RenderWindow& w);
	
	//setters
	//remove a piece from the board array
	void remove(Piece piece);
	//change the value of a position of the board list so that a new piece is made
	void place(Piece piece);
	//reset makes the board the initial starting position of all the pieces
	void reset();
	//print board lists all the values of the pieces in their positions to console
	void printBoard();
	//draw draws the board to the main window with background of a checkered pattern
	void draw();

	//returns the coordinates relative to the board from the window size
	sf::Vector2i getCoords(sf::Vector2i coords);

	//getters pretty simple stuff im not gonna explain
	Piece get(sf::Vector2i position);
	int getWidth();
	int getHeight();
};