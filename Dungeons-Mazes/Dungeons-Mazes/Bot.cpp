#include "Bot.hpp"
Bot::Bot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
}

void Bot::move() {
	m_OpenSet.push_back((Cell*)m_pMaze->m_pMap[m_Position.x][m_Position.y]);
	bool hasFoundPath = false;
	Cell* end = nullptr; //end is destination of Artifact
	Cell* start = nullptr; //start is the last/actual position
	Cell* current;
	do {
		if (m_OpenSet.size > 0) {
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

			m_OpenSet.erase(std::remove(m_OpenSet.begin(), m_OpenSet.end(), 8),
				m_OpenSet.end());
			m_ClosedSet.push_back(current);

			vector<Cell*> neighbors = current->m_pNeighbors;
			for (Cell* neighbor : neighbors) {
				if ((std::find(neighbors.begin(), neighbors.end(), neighbor) != neighbors.end() == false)
					&& neighbor->m_IsWall == false) {
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
						neighbor->m_Previous = current;
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

}