#pragma once
#include "Config.hpp"

class Maze;
class Cell : public GameObject {
public:	
	bool m_IsWall;
	Cell* m_Previous;
	vector<Cell*> m_pNeighbors;
	double m_F; // funkcja minimalizacyjna drogi
	double m_G; // ca³a przebyta droga od pocz¹tku do aktualnego
	double m_H; //przewidywana przez heurystykê droga 
	Cell(Point p, Maze* maze);
	~Cell();
	void show() override;
	void addNeighbors();
};