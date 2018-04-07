#include "Maze.hpp"

Maze::Maze(int mapSizeX, int mapSizeY) : m_MapSizeX(mapSizeX), m_MapSizeY(mapSizeY) {
	assert(mapSizeX > 0);
	assert(mapSizeY > 0);
	m_pMap = new GameObject**[mapSizeY];
	for (int i = 0; i < mapSizeY; i++) {
		m_pMap[i] = new GameObject*[mapSizeX];
	}
	for (int i = 0; i < mapSizeY; i++) {
		for (int j = 0; j < mapSizeX; j++) {
			m_pMap[i][j] = new Cell(Point(i,j), this);
			dynamic_cast<Cell*>(m_pMap[i][j])->addNeighbors();
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
	for (int i = 1; i <= m_MapSizeY; i++) {
		for (int j = 1; j <= m_MapSizeX; j++) {
			if ((i == 1 && j == 1) || (i == m_MapSizeX && j == m_MapSizeY))
				cout << "#";
			else if (i == 1 || i == m_MapSizeX)
				cout << "-";
			else if (j == 1 || j == m_MapSizeY)
				cout << "|";
 			else if (m_pMap[i-1][j-1] != nullptr) {
				m_pMap[i][j]->show();
			}
		}
		cout << endl;
	}
}

bool Maze::ifCoordExist(int p, int mapSize) {
	if (p >= 0 && p < mapSize) return true;
	else return false;
}