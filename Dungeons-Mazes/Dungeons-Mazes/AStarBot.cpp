#include "AStarBot.hpp"
#include "Artifact.hpp"

///Could use some brief explaination to not forget what is it
void AStarBot::updatePaths() {
	Cell* end;
	vector<Cell*> nextPath;
	Point tmp;
	int artifactCount = m_pMaze->m_Artifacts.size();
	if (artifactCount == 0)
		return;
	else if (artifactCount >= 1) {
		tmp = m_pMaze->m_Artifacts[0]->m_Position;
		end = m_pMaze->m_pMap[tmp.x][tmp.y].cell;
		m_Path = A_Star_Algorithm(end);
		
		if (m_Path.size() <= 1)
			return;

		for (int i = 1; i < artifactCount; i++) {
			tmp = m_pMaze->m_Artifacts[i]->m_Position;
			end = m_pMaze->m_pMap[tmp.x][tmp.y].cell;
			nextPath = A_Star_Algorithm(end);
			if (nextPath.size() <= m_Path.size()) {
				m_Path = nextPath;
			}
		}
	}
}

///Could use some brief explaination to not forget what is it
vector<Cell*> AStarBot::reconstruct_path(Cell* current) {
	Cell* tmp = current;
	vector<Cell*> path;
	path.push_back(tmp);

	while (m_DataSet[tmp]->m_pPrevious) {
		path.push_back(m_DataSet[tmp]->m_pPrevious);
		tmp = m_DataSet[tmp]->m_pPrevious;
	}

	if (path.size() >= 1)
		path.erase(path.end() - 1);
	
	for (const auto &p : m_DataSet) {
		p.second->m_pPrevious = nullptr;
		p.second->m_F = 0.0;
		p.second->m_G = 0.0;
		p.second->m_H = 0.0;
	}

	return path;
}

void AStarBot::move() {
	m_Timer.tick();

	if (m_pMaze->artifactHasJustSpawned)
		updatePaths();

	if (m_Path.empty()) {
		updatePaths();
		if (m_Path.empty())
			return;
	}

	Point next;
	next = m_Path[m_Path.size() - 1]->m_Position;

	if (m_pMaze->ifCoordExist(next.x, m_pMaze->m_MapSizeX)
		&& m_pMaze->ifCoordExist(next.y, m_pMaze->m_MapSizeY)) 
	{
		if (m_pMaze->m_pMap[next.x][next.y].artifact != nullptr) 
		{
			//cout << "ZEBRALES ARTEFAKT!" << endl;
			m_ArtifactsObtained++;
			m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
				m_pMaze->m_pMap[next.x][next.y].artifact));

			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
		else if (m_pMaze->m_pMap[next.x][next.y].NPC != nullptr) {
			//cout << endl << endl << "SPOTKALISMY SIE. NIE MOGE PRZEJSC DALEJ";

		}
		else if (!m_pMaze->m_pMap[next.x][next.y].cell->m_IsWall) {
			m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
			m_pMaze->m_pMap[next.x][next.y].NPC = this;
			m_Position = next;
		}
	}

	start = m_pMaze->m_pMap[m_Position.x][m_Position.y].cell;
	m_Path.pop_back();
	m_Timer.tock();
}

vector<Cell*> AStarBot::A_Star_Algorithm(Cell *end) {
	int pathsize = 0;

	vector<Cell*> m_OpenSet, m_ClosedSet, path;
	Cell* current = nullptr;
	bool hasFoundPath = false;
	m_OpenSet.push_back(start);

	do {
		if (m_OpenSet.size() > 0) {
			current = nullptr;
			current = m_OpenSet[0];
			for (auto node : m_OpenSet) {
				if (m_DataSet[node]->m_F < m_DataSet[current]->m_F) {
					current = node;
				}
			}

			if (current == end) {
				hasFoundPath = true;
				break;
			}

			m_OpenSet.erase(std::find(m_OpenSet.begin(), m_OpenSet.end(), current));
			m_ClosedSet.push_back(current);
			vector<Cell*> neighbors = current->m_pNeighbors;

			for (Cell* neighbor : neighbors) {
				if (!(std::find(m_ClosedSet.begin(), m_ClosedSet.end(), neighbor) != m_ClosedSet.end())
					&& !neighbor->m_IsWall) {
					
					
					//int	tmp_G = m_DataSet[current]->m_G + current->getTerrainType() + current->m_Position.getMoveWeight(neighbor->m_Position);
					float tmp_G = m_DataSet[current]->m_G + 1.0;
					bool newPath = false;
					if (std::find(m_OpenSet.begin(), m_OpenSet.end(), neighbor) != m_OpenSet.end()) {
						if (tmp_G < m_DataSet[neighbor]->m_G) {
							m_DataSet[neighbor]->m_G = tmp_G;
							newPath = true;
						}
					}
					else {
						m_DataSet[neighbor]->m_G = tmp_G;
						newPath = true;
						m_OpenSet.push_back(neighbor);
					}

					if (newPath) {
						m_DataSet[neighbor]->m_H = heuristic(neighbor->m_Position, end->m_Position);
						m_DataSet[neighbor]->m_F = m_DataSet[neighbor]->m_G + m_DataSet[neighbor]->m_H;
						m_DataSet[neighbor]->m_pPrevious = current;
					}
				}
			}
		}
	} while (!hasFoundPath);

	return reconstruct_path(current);
}

void AStarBot::show() {
#if defined(CONSOLE_VIEW_BUILD)
	cout << "A";
#endif
}

AStarBot::AStarBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	for (auto cell : m_pMaze->m_Cells) {
		if (!cell->m_IsWall) {
			m_DataSet[cell] = new Data;
		}
	}

	start = m_pMaze->m_pMap[m_Position.x][m_Position.y].cell;
};

AStarBot::~AStarBot() {
	for (auto cell : m_pMaze->m_Cells)
		delete m_DataSet[cell];

}

///Will this be ever used ? leave it be : delete
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
