#include <iostream>
#include "SFML/Graphics.hpp"
#include "Piece.h"

using namespace std;

Piece::Piece() {
	color = Color::UNDEFINED;
	x = 0;
	y = 0;
}

Piece::Piece(Color color, int x, int y){
	Piece::color = color;
	Piece::x = x;
	Piece::y = y;
}

void Piece::print() {
	switch (color) {
	case Color::BLACK:
		cout << '0';
		break;
	case Color::RED:
		cout << 'X';
		break;
	case Color::UNDEFINED:
		cout << ' ';
	}
}