#pragma once
#include "Config.hpp"

class GameObject;

class Maze {
private:
public:
	uint32_t m_MapSizeX, m_MapSizeY;
	GameObject ***m_pMap;
	GameObject ***m_pinitMap;
	vector<GameObject> m_List;

	Maze(int mapSizeX, int mapSizeY);
	~Maze();
	void Print();
	bool ifCoordExist(int p, int mapSize);

};