#include "Bot.hpp"
#include "Artifact.hpp"

void Bot::move() {
	static int moveCount = 0;
	assert(moveCount < 10);
	int a = random(0, 3);
	Point tmp;
	switch (a) {
	case 0: //right
		tmp = Point(m_Position.x + 1, m_Position.y);
		break;
	case 1:
		tmp = Point(m_Position.x - 1, m_Position.y);
		break;
	case 2:
		tmp = Point(m_Position.x, m_Position.y + 1);
		break;
	case 3:
		tmp = Point(m_Position.x, m_Position.y - 1);
		break;
	}
	if (m_pMaze->ifCoordExist(tmp.x, m_pMaze->m_MapSizeX) && m_pMaze->ifCoordExist(tmp.y, m_pMaze->m_MapSizeY)) {
		if (m_pMaze->m_pMap[tmp.x][tmp.y].artifact!=nullptr) {
			cout << "ZEBRALES ARTEFAKT!" << endl;
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].artifact = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
			m_Position.x = tmp.x;
			m_Position.y = tmp.y;
			Sleep(3000);
		}else if (!m_pMaze->m_pMap[tmp.x][tmp.y].cell->m_IsWall) {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
			m_Position.x = tmp.x;
			m_Position.y = tmp.y;
		}
		else {
			moveCount++;
			move();
		}
		moveCount = 0;
	}
}
void Bot::reconstruct_path(Cell* current) {
	m_Path.clear();
	Cell* tmp = current;
	m_Path.push_back(tmp);
	while (tmp->m_Previous) {
		m_Path.push_back(tmp->m_Previous);
		tmp = tmp->m_Previous;
	}

	//Now it has path, so it can actually move
}

void Bot::show() {
	cout << "B";
}

//void Bot::SEARCH() {
//	m_OpenSet.push_back((Cell*)m_pMaze->m_pMap[m_Position.x][m_Position.y].cell);
//	bool hasFoundPath = false;
//	Cell* end = nullptr; //end is destination of Artifact
//	Cell* start = nullptr; //start is the last/actual position
//	Cell* current = nullptr;
//	do {
//		int size = 0;//m_OpenSet.size();
//		
//		if (size > 0) {
//			current = nullptr;
//			current = m_OpenSet[0];
//			for (auto node : m_OpenSet) {
//				if (node->m_F < current->m_F) {
//					current = node;
//				}
//			}
//
//			if (current == end) {
//				m_Path.clear();
//				//done!
//				//...
//				hasFoundPath = true;
//				break;
//			}
//
//			m_OpenSet.erase(std::find(m_OpenSet.begin(), m_OpenSet.end(), current));
//			m_ClosedSet.push_back(current);
//
//			vector<Cell*> neighbors = current->m_pNeighbors;
//			for (Cell* neighbor : neighbors) {
//				if ((std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end() == false)
//					&& neighbor->m_IsWall == false) {
//
//					double tmp_G = current->m_G + 1.0;
//					bool newPath = false;
//					if (std::find(m_OpenSet.begin(), m_OpenSet.end(), neighbor) != m_OpenSet.end()) {
//						if (tmp_G < neighbor->m_G) {
//							neighbor->m_G = tmp_G;
//							newPath = true;
//						}
//					}
//					else {
//						neighbor->m_G = tmp_G;
//						newPath = true;
//						m_OpenSet.push_back(neighbor);
//					}
//
//					if (newPath) {
//						neighbor->m_H = heuristic(neighbor->m_Position, end->m_Position);
//						neighbor->m_F = neighbor->m_G + neighbor->m_H;
//						neighbor->m_Previous = current;
//					}
//				}
//			}
//		} else { //keep searching for path
//			m_Path.clear();
//		}
//
//
//	} while (!hasFoundPath);
//
//	//this->reconstruct_path(current);
//}