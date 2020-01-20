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
	sf::RenderWindow *window;

public:
	Board(sf::RenderWindow& w);
	
	//setters
	void remove(Piece piece);
	void place(Piece piece);
	void reset();
	void printBoard();
	void draw();

	sf::Vector2i getCoords(sf::Vector2i coords);

	//getters
	Piece get(sf::Vector2i position);
	int getWidth();
	int getHeight();
};