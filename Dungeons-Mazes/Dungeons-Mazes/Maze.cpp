#include "Maze.hpp"

Maze::Maze(int mapSizeX, int mapSizeY) : m_MapSizeX(mapSizeX), m_MapSizeY(mapSizeY) {
	assert(mapSizeX > 0);
	assert(mapSizeY > 0);
	m_pMap = new GameObject**[mapSizeY];
	for (int i = 0; i < mapSizeY; i++) {
		m_pMap[i] = new GameObject*[mapSizeX];
	}
	for (int i = 0; i < mapSizeY; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			m_pMap[i][j] = new Cell(Point(i,j));
		}
	}

	
}

Maze::~Maze() {
	for (int i = 0; i < m_MapSizeY; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			delete m_pMap[i][j];
		}
	}
}

void Maze::Print() {
	for (int i = 0; i < m_MapSizeY; i++) {
		for (int j = 0; j < m_MapSizeY; j++) {
			if (m_pMap[i][j] != nullptr) {
				//m_pMap[i][j]->show();
			}
		}
	}
}