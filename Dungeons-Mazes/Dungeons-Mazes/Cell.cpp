#include "Cell.hpp"

void Cell::show() {
	if (m_IsWall)
		std::cout << "*";
	else
		std::cout << " ";
}

void Cell::addNeighbors() {
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			//if (i*j == 0 && i + j != 0)	//to get 4 neighbors instead of 8
				if (!(i==0 && j==0))  //to get  8 neighbors instead of 8
				if (m_pMaze->ifCoordExist(m_Position.x + i, m_pMaze->m_MapSizeX) &&
					m_pMaze->ifCoordExist(m_Position.y + j, m_pMaze->m_MapSizeY))
					m_pNeighbors.push_back(m_pMaze->m_pMap[m_Position.x + i][m_Position.y + j].cell);
}

Cell::Cell(Point p, Maze* maze) : GameObject(p, maze) {
	m_F = 0.0;
	m_G = 0.0;
	m_H = 0.0;

	if (random() < 0.2) {
		m_IsWall = true;
	}
	else m_IsWall = false;
}

Cell::~Cell() {

}
