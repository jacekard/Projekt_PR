#pragma once
#include "Config.hpp"

class Cell : public GameObject {
private:
	Maze* m_pMaze;
	bool m_IsWall;
public:	
	vector<Cell*> m_pNeighbors;

	Cell(Point p, Maze* maze);
	~Cell();
	void show() override;
	void addNeighbors();
};