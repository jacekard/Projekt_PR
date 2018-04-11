#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class AStarBot : public AbstractPlayer {
public:
	bool isPathSet = false;
	bool pathEstablished = false;
	vector<Cell*> m_Path, m_OpenSet, m_ClosedSet;
	struct Data {
		Cell* m_pPrevious;
		double m_F; // funkcja minimalizacyjna drogi
		double m_G; // ca³a przebyta droga od pocz¹tku do aktualnego
		double m_H; //przewidywana przez heurystykê droga 
	};
	map<Cell*, Data*> m_DataSet;
	void A_Star_Algorithm();
	void reconstruct_path(Cell* current);
	Cell* findNearestArtifact();
	void show() override; //display
	void move() override; //finding path
	AStarBot(Point p, string name, Maze* maze);
	~AStarBot();
};