#include "DijkstraBot.hpp"
#include "Artifact.hpp"

void DijkstraBot::move() {

}

void DijkstraBot::DijkstraAlgotithm() {
	for (auto artifact : m_pMaze->m_Artifacts) {
		vector<Cell*> Q;
		Point artPos = artifact->m_Position;
		Cell* source = m_pMaze->m_pMap[artPos.x][artPos.y].cell;
		m_DataSet[source]->distance = 0;
		for (auto cell : m_pMaze->m_Cells) {
			if (cell != source) {
				//jezeli dla sourca bedzie mniejszy distance, przepisuj na final distance
				m_DataSet[cell]->distance=INFINITE;
				Q.push_back(cell);
			}
		}

		while (!Q.empty) {
			Cell* min;
			int dist = INFINITE;
			for (auto cell : Q) {
				if (m_DataSet[cell]->distance < dist) {
					m_DataSet[cell]->distance = dist;
					min = cell;
				}
			}
			Q.at;

		}
	}
}

DijkstraBot::DijkstraBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	for (auto cell : m_pMaze->m_Cells) {
		Data* data = new Data;
		data->distance = INFINITE;
	}
}

DijkstraBot::~DijkstraBot() {

}