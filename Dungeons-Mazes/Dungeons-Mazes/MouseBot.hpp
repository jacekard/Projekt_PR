#pragma once
#include "AbstractPlayer.hpp"

class MouseBot : public AbstractPlayer {
private:
	Point m_Vector;
public:
	void move() override;
	void show() override;
	MouseBot(Point, string, Maze*);
	~MouseBot() {};
};