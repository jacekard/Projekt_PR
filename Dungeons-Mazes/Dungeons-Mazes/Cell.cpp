#include "Cell.hpp"

void Cell::show() {
	if (m_IsWall)
		std::cout << "*";
	else
		std::cout << " ";
}

void Cell::addNeighbors() {
	if (m_pMaze->ifCoordExist(m_Position.x - 1, m_pMaze->m_MapSizeX)) 
		m_pNeighbors.push_back(m_pMaze->m_pMap[m_Position.x - 1][m_Position.y].cell);
	if (m_pMaze->ifCoordExist(m_Position.x + 1, m_pMaze->m_MapSizeX))
		m_pNeighbors.push_back(m_pMaze->m_pMap[m_Position.x + 1][m_Position.y].cell);
	if (m_pMaze->ifCoordExist(m_Position.y - 1, m_pMaze->m_MapSizeY))
		m_pNeighbors.push_back(m_pMaze->m_pMap[m_Position.x][m_Position.y - 1].cell);
	if (m_pMaze->ifCoordExist(m_Position.y + 1, m_pMaze->m_MapSizeY))
		m_pNeighbors.push_back(m_pMaze->m_pMap[m_Position.x][m_Position.y + 1].cell);
}

Cell::Cell(Point p, Maze* maze) : GameObject(p, maze) {
	m_F = 0.0;
	m_G = 0.0;
	m_H = 0.0;

	if (random() < 0.01) {
		m_IsWall = true;
	}
	else m_IsWall = false;
}

Cell::~Cell() {

}
