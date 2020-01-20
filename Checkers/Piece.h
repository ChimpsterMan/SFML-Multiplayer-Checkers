#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Piece {
public:
	enum class Color { RED, BLACK, UNDEFINED };
	Color color;
	int x;
	int y;

	Piece();
	Piece(Color color, int x, int y);

	void print();
};