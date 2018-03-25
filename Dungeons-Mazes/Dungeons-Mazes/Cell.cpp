#include "Cell.hpp"

void Cell::show() {
	std::cout << "*";
}

Cell::Cell(Point p) : GameObject(p) {
	if (random() < 0.2) {
		m_IsWall = true;
	}
	else m_IsWall = false;
}

Cell::~Cell() {

}