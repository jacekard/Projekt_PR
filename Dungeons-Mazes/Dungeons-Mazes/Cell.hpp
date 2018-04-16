#pragma once
#include "GameObject.hpp"
#include "Maze.hpp"

enum TerrainType {
	FLOOR = 0,
	WALL = INFINITE,
	WATER = 5,
	SHREKSWAMP = 1000
};

class Cell : public GameObject {
public:	
	bool m_IsWall;
	Point m_Vector;
	TerrainType m_Terrain;
	vector<Cell*> m_pNeighbors;
	int getTerrainType();
	void addNeighbors(Node** map);
	void show() override;
	Cell(Point p, Maze* maze, bool isWall);
	~Cell();
};