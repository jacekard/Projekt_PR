#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class PledgeBot: public AbstractPlayer {
public:
	Point m_Vector;

	void Pledge();
	void show() override;
	void move() override;
	PledgeBot(Point p, string name, Maze* maze);
	~PledgeBot();
};