#pragma once
#include "GameObject.hpp"
#include "Maze.hpp"

class Cell : public GameObject {
public:	
	bool m_IsWall;
	Cell* m_pPrevious;
	vector<Cell*> m_pNeighbors;
	double m_F; // funkcja minimalizacyjna drogi
	double m_G; // ca³a przebyta droga od pocz¹tku do aktualnego
	double m_H; //przewidywana przez heurystykê droga 
	Cell(Point p, Maze* maze, bool isWall);
	~Cell();
	void show() override;
	void addNeighbors();
};