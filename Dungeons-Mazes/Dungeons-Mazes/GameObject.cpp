#include "GameObject.hpp"
#include "Maze.hpp"
#include "Cell.hpp"

Cell* GameObject::getMotherCell() {
	return m_pMaze->m_pMap[m_Position.x][m_Position.y].cell;
}