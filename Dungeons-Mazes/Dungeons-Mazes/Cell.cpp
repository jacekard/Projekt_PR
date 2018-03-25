#include "Cell.hpp"

void Cell::show() {
	std::cout << "*";
}

void Cell::addNeighbors() {
	if (m_pMaze->ifCoordExist(m_Position.x - 1, m_pMaze->m_MapSizeX)) 
		m_pNeighbors.push_back((Cell*)m_pMaze->m_pMap[m_Position.x - 1][m_Position.y]);
	if (m_pMaze->ifCoordExist(m_Position.x + 1, m_pMaze->m_MapSizeX))
		m_pNeighbors.push_back((Cell*)m_pMaze->m_pMap[m_Position.x + 1][m_Position.y]);
	if (m_pMaze->ifCoordExist(m_Position.y - 1, m_pMaze->m_MapSizeY))
		m_pNeighbors.push_back((Cell*)m_pMaze->m_pMap[m_Position.x][m_Position.y - 1]);
	if (m_pMaze->ifCoordExist(m_Position.y + 1, m_pMaze->m_MapSizeY))
		m_pNeighbors.push_back((Cell*)m_pMaze->m_pMap[m_Position.x][m_Position.y + 1]);
}

Cell::Cell(Point p, Maze* maze) : GameObject(p) {
	m_pMaze = maze;

	if (random() < 0.2) {
		m_IsWall = true;
	}
	else m_IsWall = false;
}

Cell::~Cell() {

}
