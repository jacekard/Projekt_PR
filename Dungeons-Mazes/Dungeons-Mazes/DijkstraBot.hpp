#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class DijkstraBot : public AbstractPlayer {
public:
	stack<Cell*> m_Path;
	struct Data {
		unsigned int distance;
	};
	map<Cell*, Data*> m_DataSet;

	void DijkstraAlgorithm();
	void getPath();
	void show() override;
	void move() override;
	DijkstraBot(Point, PlayerType, Maze*);
	~DijkstraBot();
};