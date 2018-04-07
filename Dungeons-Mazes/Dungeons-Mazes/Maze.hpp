#pragma once
#include "Config.hpp"


class GameObject;
class AbstractPlayer;
struct Node {
	GameObject* cell;
	GameObject* NPC;
};
class Maze {
public:
	uint32_t m_MapSizeX, m_MapSizeY;
	Node **m_pMap;
	Node **m_pinitMap;
	vector<GameObject*> m_List;
	vector<AbstractPlayer*> bots;
	vector<AbstractPlayer*> players;
	Maze(int mapSizeX, int mapSizeY);
	~Maze();
	void Print();
	bool ifCoordExist(int p, int mapSize);

};