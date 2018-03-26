#pragma once
#include "Config.hpp"

class Maze;
class Cell : public GameObject {
public:	
	Maze* m_pMaze;
	bool m_IsWall;
	Cell* m_Previous;
	vector<Cell*> m_pNeighbors;
	double m_F; // funkcja minimalizacyjna drogi
	double m_G; // ca�a przebyta droga od pocz�tku do aktualnego
	double m_H; //przewidywana przez heurystyk� droga 
	Cell(Point p, Maze* maze);
	~Cell();
	void show() override;
	void addNeighbors();
};