#include "DijkstraBot.hpp"
#include "Artifact.hpp"
void DijkstraBot::move() {
	//trzeba zrobic jakas fancy uniwersalna funkcje, ktora handluje nam akcje gdy wejdzie na nastepne pole, a tutaj tylko okreslac pole
	m_Timer.tick();

	if (m_pMaze->artifactHasJustSpawned) //trzeba tez zrobic dijkstre kiedy docelowe pole straci artefakt, 
		DijkstraAlgotithm();			 //czyli cos w stylu if(m_Path.bot ->artifact == nullptr), wiec chyba nie obejdzie sie bez zmiany
										 //stack na vector

	if (m_Path.empty()) {
		DijkstraAlgotithm();
		if (m_Path.empty())
			return;
	}

	Point next = m_Path.top()->m_Position;
	m_Path.pop();
	if (m_pMaze->m_pMap[next.x][next.y].artifact != nullptr) {
		cout << "ZEBRALES ARTEFAKT!" << endl;
		artifactsObtained++;

		m_pMaze->m_Artifacts.erase(std::find(m_pMaze->m_Artifacts.begin(), m_pMaze->m_Artifacts.end(),
			m_pMaze->m_pMap[next.x][next.y].artifact));

		m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
		m_pMaze->m_pMap[next.x][next.y].artifact = nullptr;
		m_pMaze->m_pMap[next.x][next.y].NPC = this;
		m_Position = next;
		DijkstraAlgotithm();
	}
	else if (m_pMaze->m_pMap[next.x][next.y].NPC != nullptr) {
		cout << endl << endl << "SPOTKALISMY SIE. NIE MOGE PRZEJSC DALEJ";
	}
	else {
		m_pMaze->m_pMap[m_Position.x][m_Position.y].NPC = nullptr;
		m_pMaze->m_pMap[next.x][next.y].NPC = this;
		m_Position = next;
	}

	m_Timer.tock();
}

void DijkstraBot::getPath() {
	Artifact* nearestArtifact = nullptr;
	unsigned int minDistance = INFINITE;

	if (m_pMaze->m_Artifacts.size() == 0) return;
	for (auto artifact : m_pMaze->m_Artifacts) {
		Cell* motherCell = artifact->getMotherCell();

		if (m_DataSet[motherCell]->distance < minDistance) {
			minDistance = m_DataSet[motherCell]->distance;
			nearestArtifact = artifact;
		}
	}

	m_Path = stack<Cell*>();
	Cell* actualCell = nearestArtifact->getMotherCell();
	m_Path.push(actualCell);
	while (actualCell != getMotherCell()) {
		for (auto neighbor : actualCell->m_pNeighbors) {
			if (!neighbor->m_IsWall) {
				if (m_DataSet[neighbor]->distance == m_DataSet[actualCell->getMotherCell()]->distance - 1) {//ten warunek trzeba zmienic, gdy wprowadzimy koszty
					m_Path.push(neighbor);
					actualCell = neighbor;
					break;
				}
			}
		}
	}
	m_Path.pop();
}

struct comp {
	comp(pair<Cell*, unsigned int> input) : _input(input) {}
	bool operator()(pair<Cell*, unsigned int> iPair) {
		return (iPair.first == _input.first && iPair.second == _input.second);
	}
	pair<Cell*, unsigned int> _input;
};

void DijkstraBot::DijkstraAlgotithm() {
	//ten algorytm jest teraz praktycznie BFSem, zmieni to siê kiedy dodane zostan¹ wagi terenu
	//zmieni³em go w taki sposob, ze tak naprawde naszym celem jest bot, a to artefakty chca sie do niego dostac
	vector<pair<Cell*, unsigned int>> Q;
	Cell* source = m_pMaze->m_pMap[m_Position.x][m_Position.y].cell;
	m_DataSet[source]->distance = 0;
	Q.push_back(pair<Cell*, unsigned int>(source, 0));

	for (auto cell : m_pMaze->m_Cells) {
		if (cell != source && !cell->m_IsWall) {
			m_DataSet[cell]->distance = INFINITE;
			Q.push_back(pair<Cell*, unsigned int>(cell, INFINITE));
		}
	}
	while (!Q.empty()) {
		Cell* min = Q[0].first;
		Q.erase(Q.cbegin());
		for (auto neighbor : min->m_pNeighbors) {
			if (!neighbor->m_IsWall) {
				unsigned int alt = m_DataSet[min]->distance + 1;//+waga(min, neighbor); tutaj zamiast 1 bedzie waga
				if (alt < m_DataSet[neighbor]->distance) {

					auto it = find_if(Q.begin(), Q.end(), comp(pair<Cell*, unsigned int>(neighbor, m_DataSet[neighbor]->distance)));
					if (it != Q.end()) {
						Q.erase(it);
						Q.push_back(pair<Cell*, unsigned int>(neighbor, alt));
						sort(Q.begin(), Q.end(), [](const auto &lhs, const auto &rhs) -> bool {
							return rhs.second > lhs.second;
						});
					}
					m_DataSet[neighbor]->distance = alt;
				}
			}
		}
	}
	getPath();
}

void DijkstraBot::show() {
	cout << "D";
}

DijkstraBot::DijkstraBot(Point p, string name, Maze* maze) : AbstractPlayer(p, name, maze) {
	for (auto cell : m_pMaze->m_Cells) {
		Data* data = new Data;
		data->distance = INFINITE;
		m_DataSet[cell] = data;
	}
}

DijkstraBot::~DijkstraBot() {

}