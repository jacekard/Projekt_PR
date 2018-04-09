#include "MouseBot.hpp"
#include "Maze.hpp"
#include "Cell.hpp";

void MouseBot::move() {
	Point tmp = Point(m_Position.x + m_Vector.x, m_Position.y + m_Vector.y);
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
			m_Vector = randomVector(m_Vector); //przyjecie parametru wyklucza go z losowania
			move();
		}
	}else {
		m_Vector = randomVector(m_Vector); //przyjecie parametru wyklucza go z losowania
		move();
	}
}

void MouseBot::show() {
	cout << "~";
}

MouseBot::MouseBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	m_Vector = UP;
};