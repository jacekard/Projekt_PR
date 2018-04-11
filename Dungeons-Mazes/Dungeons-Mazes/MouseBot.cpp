#include "MouseBot.hpp"
#include "Maze.hpp"
#include "Cell.hpp"

////////////////////////////////////////////////////////////
/// Function move
/// @brief this bot moves forward, when stumbling on wall
///     tries to turn right and continue
////////////////////////////////////////////////////////////
void MouseBot::move() {
	Point tmp;
	if (straight) {
		Point tmpVector = m_Vector;
		tmpVector.turnRight();
		tmp = m_Position + tmpVector;
		if (m_pMaze->ifCoordExist(tmp.x, m_pMaze->m_MapSizeX) && m_pMaze->ifCoordExist(tmp.y, m_pMaze->m_MapSizeY)) {
			if (!m_pMaze->m_pMap[tmp.x][tmp.y].cell->m_IsWall) {
				straight = false;
				m_Vector = tmpVector;
				move();
			}
		}
	}
	straight = true;
	tmp = m_Position + m_Vector;


	if (m_pMaze->ifCoordExist(tmp.x, m_pMaze->m_MapSizeX) && m_pMaze->ifCoordExist(tmp.y, m_pMaze->m_MapSizeY)) {
		if (m_pMaze->m_pMap[tmp.x][tmp.y].artifact != nullptr) {
			cout << "ZEBRALES ARTEFAKT!" << endl;
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].artifact = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
			m_Position = tmp;
		}
		else if (!m_pMaze->m_pMap[tmp.x][tmp.y].cell->m_IsWall) {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
			m_Position = tmp;
		}
		else {
			straight = false;
			m_Vector.turnRight();
		}
	}
	else {
		straight = false;
		m_Vector.turnRight();
	}
}

void MouseBot::show() {
	cout << "~";
}

MouseBot::MouseBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	m_Vector = UP;
	straight = false;
};