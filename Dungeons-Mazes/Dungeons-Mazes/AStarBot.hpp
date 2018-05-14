#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class AStarBot : public AbstractPlayer {
public:
	bool isPathSet = false;
	bool pathEstablished = false;
	vector<Cell*> m_Path, m_Empty;
	Cell* start;
	Artifact* m_pNearestArtifact;

	struct Data {
		Cell* m_pPrevious = nullptr;
		float m_F = 0.0; // funkcja minimalizacyjna drogi
		float m_G = 0.0; // ca³a przebyta droga od pocz¹tku do aktualnego
		float m_H = 0.0; // przewidywana przez heurystykê droga 
	};

	map<Cell*, Data*> m_DataSet;
	vector<Cell*> A_Star_Algorithm(Cell *end);
	vector<Cell*> reconstruct_path(Cell* current);
	void updatePaths();
	void show() override; //display
	void move() override; //finding path
	AStarBot(Point, PlayerType, Maze*);
	~AStarBot();
};