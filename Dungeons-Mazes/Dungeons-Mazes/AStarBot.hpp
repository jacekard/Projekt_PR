#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class AStarBot : public AbstractPlayer {
public:
	bool isPathSet = false;
	bool pathEstablished = false;
	vector<Cell*> m_Path, m_OpenSet, m_ClosedSet;
	AStarBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {};
	~AStarBot();
	void show() override; //display
	void move() override; //finding path
	void A_Star_Algorithm();
	void reconstruct_path(Cell* current);
	Cell* findNearestArtifact();
};