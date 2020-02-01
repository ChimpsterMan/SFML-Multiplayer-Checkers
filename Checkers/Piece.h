#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

//simple data structure for a piece
class Piece {
public:
	//3 types of color available
	enum class Color { RED, BLACK, UNDEFINED };
	Color color;
	int x;
	int y;

	//empty specifications automatically is set to (0,0) and undefined color
	Piece();
	//put in data about it
	Piece(Color color, int x, int y);

	//print to console the color of the piece
	void print();
};