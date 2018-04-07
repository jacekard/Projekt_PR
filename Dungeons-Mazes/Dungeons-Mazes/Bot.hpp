#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class Bot : public AbstractPlayer {
public:
	vector<Cell*> m_Path, m_OpenSet, m_ClosedSet;
	Bot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {};
	~Bot();
	void show() override; //display
	void move() override; //finding path
	void reconstruct_path(Cell* current);
};