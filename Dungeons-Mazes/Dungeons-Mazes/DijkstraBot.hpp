#pragma once
#include "AbstractPlayer.hpp"
#include "Cell.hpp"

class DijkstraBot : public AbstractPlayer {
public:
	struct Data {
		int finalDist;
		int distance;
	};
	map<Cell*, Data*> m_DataSet;
	Artifact* m_pNearestArtifact;

	void DijkstraAlgotithm();
	void show() override;
	void move() override;
	DijkstraBot(Point p, string name, Maze* maze);
	~DijkstraBot();
};