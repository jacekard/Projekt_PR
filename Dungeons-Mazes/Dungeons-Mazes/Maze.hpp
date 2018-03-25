#pragma once
#include "Config.hpp"

class GameObject;

class Maze {
private:
	uint32_t m_MapSizeX, m_MapSizeY;
	GameObject ***m_pMap;
	GameObject ***m_pinitMap;
	vector<GameObject> m_List;
public:
	Maze(int mapSizeX, int mapSizeY);
	~Maze();
	void Print();
};