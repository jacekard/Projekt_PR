#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class AStarBot : public AbstractPlayer {
public:
	bool isPathSet = false;
	bool pathEstablished = false;
	vector<Cell*> m_Path, m_OpenSet, m_ClosedSet;
	Artifact* m_pNearestArtifact;
	struct Data {
		Cell* m_pPrevious = nullptr;
		double m_F = 0.0; // funkcja minimalizacyjna drogi
		double m_G = 0.0; // ca³a przebyta droga od pocz¹tku do aktualnego
		double m_H = 0.0; //przewidywana przez heurystykê droga 
	};
	map<Cell*, Data*> m_DataSet;
	vector<Cell*> A_Star_Algorithm(Cell *end, Cell* start);
	vector<Cell*> reconstruct_path(Cell* current);
	Cell* findNearestArtifact();
	void updateNearest();
	void show() override; //display
	void move() override; //finding path
	AStarBot(Point p, string name, Maze* maze);
	~AStarBot();
};