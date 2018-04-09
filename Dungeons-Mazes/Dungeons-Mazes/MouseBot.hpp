#pragma once
#include "AbstractPlayer.hpp"

class MouseBot : public 
	AbstractPlayer {
private:
	Point m_Vector;
public:
	void move();
	void show();
	MouseBot(Point, string, Maze*);
	~MouseBot() {};
};