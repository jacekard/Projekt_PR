#include "Cell.hpp"

void Cell::show() {
#if defined(CONSOLE_VIEW_BUILD)
	if (m_IsWall)
		std::cout << (char)178;
	else
		std::cout << " ";
#endif
}

void Cell::addNeighbors(Node** map) {
	for (int i = -1; i <= 1; i++)
		for (int j = -1; j <= 1; j++)
			//if (i*j == 0 && i + j != 0)	//to get 4 neighbors instead of 8
			if (!(i == 0 && j == 0))  //to get 8 neighbors instead of 4
				if (m_pMaze->ifCoordExist(m_Position.x + i, m_pMaze->m_MapSizeX) &&
					m_pMaze->ifCoordExist(m_Position.y + j, m_pMaze->m_MapSizeY))
					m_pNeighbors.push_back(map[m_Position.x + i][m_Position.y + j].cell);
}

Cell::Cell(Point p, Maze* maze, bool isWall) : GameObject(p, maze) {
	m_IsWall = isWall ? true : false;
	m_Terrain = FLOOR;
}

int Cell::getTerrainType() {
	return m_Terrain;
}

Cell::~Cell() {

}
