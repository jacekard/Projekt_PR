#pragma once
#include "Config.hpp"


class GameObject;
class AbstractPlayer;
class Artifact;
class Cell;
struct Node {
	Cell* cell;
	AbstractPlayer* NPC;
	Artifact * artifact;
};
class Maze {
public:
	uint8_t m_MapSizeX, m_MapSizeY;
	uint8_t m_MaxArtifactCount;
	Node **m_pMap;
	Node **m_pinitMap;
	vector<Cell*> m_Cells;
	vector<Artifact*> m_Artifacts;
	vector<AbstractPlayer*> m_Characters;
	Maze(uint8_t mapSizeX, uint8_t mapSizeY, uint8_t m_MaximumArtifactCount);
	~Maze();
	void initializeRandomMaze(double randomFactor);
	void initializeIsleMaze(int isleCount, double randomFactor);
	void initializeProceduralMaze();
	void Print();
	bool ifCoordExist(int p, int mapSize);
	void recursiveWallPlacing(Cell *cell, double randomFactor);
	void spawnArtifact(double randomFactor);
	void spawnBot(string type);
};