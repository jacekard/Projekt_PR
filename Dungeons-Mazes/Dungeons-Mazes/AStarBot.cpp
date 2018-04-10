#include "AStarBot.hpp"
#include "Artifact.hpp"


void AStarBot::reconstruct_path(Cell* current) {
	m_Path.clear();
	Cell* tmp = current;
	m_Path.push_back(tmp);
	while (tmp->m_pPrevious) {
		m_Path.push_back(tmp->m_pPrevious);
		tmp = tmp->m_pPrevious;
	}
	isPathSet = true;
	//std::reverse(m_Path.begin(), m_Path.end());
	//Now it has path, so it can actually move
	pathEstablished = true;
}

void AStarBot::move() {
	A_Star_Algorithm();

	if (m_Path.size() <= 0) {
		return;
	}
	Point next;
	if (m_Path[m_Path.size() - 1] != nullptr
		&& m_Path[m_Path.size() - 2] != nullptr) // && m_Path[m_Path.size() - 1]->m_Position == m_Position ) 
	{
		m_Path.erase(m_Path.end() - 1);
		next = m_Path[m_Path.size() - 1]->m_Position;

	}

	if (m_pMaze->ifCoordExist(next.x, m_pMaze->m_MapSizeX)
		&& m_pMaze->ifCoordExist(next.y, m_pMaze->m_MapSizeY)) {
		if (m_pMaze->m_pMap[next.x][next.y].artifact != nullptr) {
			cout << "ZEBRALES ARTEFAKT!" << endl;

			//gdyby uzyc słownika usuwanie byloby szybsze??
			m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
				m_pMaze->m_pMap[next.x][next.y].artifact));

			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
		else if (!m_pMaze->m_pMap[next.x][next.y].cell->m_IsWall) {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
	}
}

void AStarBot::show() {
	cout << "B";
}

Cell* AStarBot::findNearestArtifact() {
	Artifact* nearest;
	Point p;
	size_t size = m_pMaze->m_Artifacts.size();
	if (size == 0) {
		return nullptr;
	}
	else if (size == 1) {
		p = m_pMaze->m_Artifacts[0]->m_Position;
		return m_pMaze->m_pMap[p.x][p.y].cell;
	}
	nearest = m_pMaze->m_Artifacts[0]; //...
	double dist = distance(nearest->m_Position, this->m_Position);
	for (size_t i = 0; i < size; i++) {
		if (distance(m_pMaze->m_Artifacts[i]->m_Position,
			this->m_Position) < dist) {
			nearest = m_pMaze->m_Artifacts[i];
		}
	}
	p = nearest->m_Position;
	return m_pMaze->m_pMap[p.x][p.y].cell;
}

void AStarBot::A_Star_Algorithm() {
#if defined(_DEBUG)
	m_OpenSet.clear();
	m_ClosedSet.clear();
	m_Path.clear();
	int blockedNeighbors = 0;
#endif


	Cell* end = findNearestArtifact(); //end is destination of Artifact
	if (end == nullptr)
		return;
	bool hasFoundPath = false;
	Cell* start = m_pMaze->m_pMap[m_Position.x][m_Position.y].cell; //start is the last/actual position
	Cell* current = nullptr;
	m_OpenSet.push_back(start);

	//* bez tego nie działa
	for (auto cell : m_pMaze->m_Cells) {
		cell->m_pPrevious = nullptr;
	}
	//*

	do {
		if (m_OpenSet.size() > 0) {
			current = nullptr;
			current = m_OpenSet[0];
			for (auto node : m_OpenSet) {
				if (node->m_F < current->m_F) {
					current = node;
				}
			}

			if (current == end) {
				m_Path.clear();
				//done!
				//...
				hasFoundPath = true;
				break;
			}

			m_OpenSet.erase(std::find(m_OpenSet.begin(), m_OpenSet.end(), current));
			m_ClosedSet.push_back(current);

			vector<Cell*> neighbors = current->m_pNeighbors;
			for (Cell* neighbor : neighbors) {
				if (!(std::find(m_ClosedSet.begin(), m_ClosedSet.end(), neighbor) != m_ClosedSet.end())
					&& !neighbor->m_IsWall) {

					//DEBUG
					blockedNeighbors = 0;
					//DEBUG

					double tmp_G = current->m_G + 1.0;
					bool newPath = false;
					if (std::find(m_OpenSet.begin(), m_OpenSet.end(), neighbor) != m_OpenSet.end()) {
						if (tmp_G < neighbor->m_G) {
							neighbor->m_G = tmp_G;
							newPath = true;
						}
					}
					else {
						neighbor->m_G = tmp_G;
						newPath = true;
						m_OpenSet.push_back(neighbor);
					}

					if (newPath) {
						neighbor->m_H = heuristic(neighbor->m_Position, end->m_Position);
						neighbor->m_F = neighbor->m_G + neighbor->m_H;
						neighbor->m_pPrevious = current;
					}
				}
			}
		}
		else { //keep searching for path
			m_Path.clear();
		}
	} while (!hasFoundPath);

	this->reconstruct_path(current);
}

//void Bot::move() {
//	static int moveCount = 0;
//	assert(moveCount < 10);
//	int a = random(0, 3);
//	Point tmp;
//	switch (a) {
//	case 0: //right
//		tmp = Point(m_Position.x + 1, m_Position.y);
//		break;
//	case 1:
//		tmp = Point(m_Position.x - 1, m_Position.y);
//		break;
//	case 2:
//		tmp = Point(m_Position.x, m_Position.y + 1);
//		break;
//	case 3:
//		tmp = Point(m_Position.x, m_Position.y - 1);
//		break;
//	}
//	if (m_pMaze->ifCoordExist(tmp.x, m_pMaze->m_MapSizeX) && m_pMaze->ifCoordExist(tmp.y, m_pMaze->m_MapSizeY)) {
//		if (m_pMaze->m_pMap[tmp.x][tmp.y].artifact != nullptr) {
//			cout << "ZEBRALES ARTEFAKT!" << endl;
//			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
//			m_pMaze->m_pMap[tmp.x][tmp.y].artifact = nullptr;
//			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
//			m_Position = tmp;
//			Sleep(3000);
//		}
//		else if (!m_pMaze->m_pMap[tmp.x][tmp.y].cell->m_IsWall) {
//			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
//			m_pMaze->m_pMap[tmp.x][tmp.y].NPC = this;
//			m_Position = tmp;
//		}
//		else {
//			moveCount++;
//			move();
//		}
//		moveCount = 0;
//	}
//}
