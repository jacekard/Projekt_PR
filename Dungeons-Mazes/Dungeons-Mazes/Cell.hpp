#pragma once
#include "GameObject.hpp"
#include "Maze.hpp"

class Cell : public GameObject {
public:	
	bool m_IsWall;
	Point m_Vector;
	vector<Cell*> m_pNeighbors;

	void addNeighbors();
	void show() override;
	Cell(Point p, Maze* maze, bool isWall);
	~Cell();
};