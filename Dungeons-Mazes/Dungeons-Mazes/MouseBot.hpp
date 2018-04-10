#pragma once
#include "AbstractPlayer.hpp"

class MouseBot : public AbstractPlayer {
private:
	Point m_Vector;
public:
	bool straight;
	void move() override;
	void show() override;
	MouseBot(Point, string, Maze*);
	~MouseBot() {};
};