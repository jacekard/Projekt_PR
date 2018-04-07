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
	uint32_t m_MapSizeX, m_MapSizeY;
	Node **m_pMap;
	Node **m_pinitMap;
	vector<Artifact*> m_Artifacts;
	vector<AbstractPlayer*> m_Characters;
	Maze(int mapSizeX, int mapSizeY);
	~Maze();
	void Print();
	bool ifCoordExist(int p, int mapSize);

};