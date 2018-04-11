#include "AStarBot.hpp"
#include "Artifact.hpp"

AStarBot::AStarBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	if (m_pMaze->m_Artifacts.size() >= 1) {
		m_pNearestArtifact = m_pMaze->m_Artifacts[0];
	}
	updateNearest();
};

void AStarBot::updateNearest() { // ???????
	size_t size = m_pMaze->m_Artifacts.size();
	double dist = distance(m_pNearestArtifact->m_Position, this->m_Position);
	for (size_t i = 1; i < size; i++) {
		if (distance(m_pMaze->m_Artifacts[i]->m_Position,
			this->m_Position) < dist) {
			m_pNearestArtifact = m_pMaze->m_Artifacts[i];
		}
		//else if ( dist == ...)
	}
}

void AStarBot::reconstruct_path(Cell* current) {
	m_Path.clear();
	Cell* tmp = current;
	Cell* delPrevious = current;
	m_Path.push_back(tmp);
	while (tmp->m_pPrevious) {
		m_Path.push_back(tmp->m_pPrevious);
		tmp = tmp->m_pPrevious;
	}
	for (auto cell : m_pMaze->m_Cells) {
		cell->m_pPrevious = nullptr;
		cell->m_F = 0.0;
		cell->m_G = 0.0;
		cell->m_H = 0.0;
	}
}

void AStarBot::move() {
	if (!hasMoved) {
		timer.start();
		hasMoved = true;
	}

	A_Star_Algorithm();

	if (m_Path.size() <= 1) {
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

			m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
				m_pMaze->m_pMap[next.x][next.y].artifact));

			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;

			findNearestArtifact(); // ?????

		}
		/*else if (m_pMaze->m_pMap[next.x][next.y].NPC!=nullptr) {
			cout << endl << endl << "SPOTKALISMY SIE. NIE MOGE PRZEJSC DALEJ";
		}*/
		else if (!m_pMaze->m_pMap[next.x][next.y].cell->m_IsWall) {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
	}

	if (m_pMaze->m_Artifacts.size() == 0) { 	//warunek zakończenia mierzenia czasu
		timer.end();
		cout << timer.getSecondsFromStart() << endl;
	}
}

Cell* AStarBot::findNearestArtifact() {
	Point p;
	size_t size = m_pMaze->m_Artifacts.size();
	if (size == 0) {
		return nullptr;
	}
	else {
		m_pNearestArtifact = m_pMaze->m_Artifacts[random(0, size - 1)];
	}

	for (size_t i = 1; i < size; i++) {
		if (distance(m_pMaze->m_Artifacts[i]->m_Position, m_Position) 
			< distance(m_pNearestArtifact->m_Position, m_Position)) {
			m_pNearestArtifact = m_pMaze->m_Artifacts[i];
		}
	}
	p = m_pNearestArtifact->m_Position;
	return m_pMaze->m_pMap[p.x][p.y].cell;
}

void AStarBot::A_Star_Algorithm() {
#if defined(_DEBUG)
	m_OpenSet.clear();
	m_ClosedSet.clear();
	m_Path.clear();
	int blockedNeighbors = 0;
#endif

	updateNearest();
	//end is destination of Artifact
	Cell* end = m_pMaze->m_pMap[m_pNearestArtifact->m_Position.x][m_pNearestArtifact->m_Position.y].cell; 
	if (end == nullptr)
		return;
	bool hasFoundPath = false;
	Cell* start = m_pMaze->m_pMap[m_Position.x][m_Position.y].cell; //start is the last/actual position
	Cell* current = nullptr;
	m_OpenSet.push_back(start);

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

void AStarBot::show() {
	cout << "B";
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
